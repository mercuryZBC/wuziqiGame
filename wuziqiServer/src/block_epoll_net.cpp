#include "block_epoll_net.h"
#include "packdef.h"
#include <csignal>
#include <sys/socket.h>
#include <sys/time.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

bool Block_Epoll_Net::InitOpenSSL(){
    /* SSL 库初始化 */
    SSL_library_init();
    /* 载入所有 SSL 算法 */
    OpenSSL_add_all_algorithms();
    /* 载入所有 SSL 错误消息 */
    SSL_load_error_strings();
    /* 以 SSL V2 和 V3 标准兼容方式产生一个 SSL_CTX ，即 SSL Content Text */
    m_ctx = SSL_CTX_new(SSLv23_server_method());
    /* 也可以用 SSLv2_server_method() 或 SSLv3_server_method() 单独表示 V2 或 V3标准 */
    if (m_ctx == NULL) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    /* 载入用户的数字证书， 此证书用来发送给客户端。 证书里包含有公钥 */
    if (SSL_CTX_use_certificate_file(m_ctx, SERVER_CACERT, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    /* 载入用户私钥 */
    if (SSL_CTX_use_PrivateKey_file(m_ctx, SERVER_PRIVATEKEY, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    /* 检查用户私钥是否正确 */
    if (!SSL_CTX_check_private_key(m_ctx)) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    printf("openssl init success...\n");
    return true;
}


bool Block_Epoll_Net::InitNet(int port, void (*recv_callback)(int, char *, int))
{
    m_recv_callback = recv_callback;
    InitThreadPool();

    int flags = 1;
    int ret = 0;
    m_listenEv = new myevent_s(this);

    //creat a tcp socket
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( m_listenfd  == -1 ){
        perror("create socket error");
        return false;
    }

    //set REUSERADDR
    ret = setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&flags, sizeof(flags));
    if ( ret == -1 ){
        perror("setsockopt error");
        return false;
    }

    //监听套接字m_listenfd 采用 LT 非阻塞模式
    //set NONBLOCK
    setNonBlockFd( m_listenfd );

    struct sockaddr_in local_addr;
    bzero( &local_addr , sizeof(sockaddr_in) );
    //set address
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    //bind addr
    ret = bind(m_listenfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
    if( ret == -1 ) {
        perror("bind error");
        close(m_listenfd);
        return false;
    }

    if (listen(m_listenfd, 128) == -1 ){
        perror("listen error");
        close(m_listenfd);
        return false;
    }

    //create epoll
    m_epoll_fd = epoll_create( MAX_EVENTS );

    m_listenEv->eventset(m_listenfd ,m_epoll_fd,nullptr);
    //将监听套接字 添加到epoll中 , 模式LT 非阻塞
    m_listenEv->eventadd( EPOLLIN);


    return true;
}

bool Block_Epoll_Net::InitThreadPool()
{

    m_threadpool = new thread_pool;

    //创建拥有10个线程的线程池 最大线程数200 环形队列最大值50000
    if( (m_threadpool->Pool_create(200,10,50000)) == false )
    {
        perror("Create Thread_Pool Failed:");
        exit(-1);
    }

    return true;
}

void Block_Epoll_Net::EventLoop()
{
    printf("EventLoop:server running\n");
    int  i = 0;
    // struct itimerval iti;
    // struct itimerval old_iti;
    // struct timeval new_tval;
    // new_tval.tv_sec = 0;
    // new_tval.tv_usec = 100000;//100毫秒
    // iti.it_interval = new_tval;
    // iti.it_value = new_tval;
    // setitimer(ITIMER_REAL,&iti,&old_iti);
    // signal(SIGALRM, sighander);
    
    while (1) {

        /* 等待事件发生 */
        int nfd = epoll_wait( m_epoll_fd, events, MAX_EVENTS+1, 1000);
        if (nfd < 0) {
            printf("epoll_wait error, exit\n");
//            break;
            continue;
        }
        for (i = 0; i < nfd; i++) {
            struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;
            int fd = ev->fd;
            if ( (events[i].events & EPOLLIN) ) {
                if( fd == m_listenfd )
                    accept_event();
                else
                    recv_event( ev );
            }
            if ((events[i].events & EPOLLOUT) ) {
                epollout_event( ev );
            }
        }
    }
}

void Block_Epoll_Net::accept_event()
{
    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    int clientfd ;
    if ((clientfd = accept(m_listenfd, (struct sockaddr *)&caddr, &len))>0) {
        /* 基于 ctx 产生一个新的 SSL */
        SSL *ssl = SSL_new(m_ctx);
        /* 将连接用户的 socket 加入到 SSL */
        SSL_set_fd(ssl, clientfd);
        /* 建立 SSL 连接 */
        if (SSL_accept(ssl) == -1) {
            perror("accept");
            close(clientfd);
            printf("ssl accept failed\n");
            return;
        }else{
            m_mapSocketToSSL.insert(clientfd, ssl);
            printf("ssl_accept success fd:%d\n",clientfd);
        }

        //设置发送缓冲区大小
        setSendBufSize(clientfd);
        //设置接收缓冲器大小
        setRecvBufSize( clientfd );
        //设置 无延迟
        setNoDelay( clientfd );

        myevent_s * clientEv = new myevent_s(this);
        clientEv->eventset( clientfd , m_epoll_fd,ssl);
        // 使用EPOLLONESHOT epoll监听不会重复检测 避免多线程并发 使得同一个套接字接收是排队的
        clientEv->eventadd(  EPOLLIN/*|EPOLLET*/|EPOLLONESHOT );

        //m_mapSockfdToEvent[clientfd] = clientEv;
        m_mapSockfdToEvent.insert(clientfd , clientEv);

        printf("new connect [%s:%d][time:%ld] \n",
            inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port), time(NULL) );

    }else{
        if (errno != EAGAIN && errno != EINTR) {
            /* 暂时不做出错处理 */
        }
        printf("%s: accept, %s\n", __func__, strerror(errno));
        return;
    }

    return;
}




void Block_Epoll_Net::recv_event( myevent_s *ev)
{
    //接收事件采用线程池 多线程处理, 由于使用EPOLLONESHOT , 避免同一套机字的线程并发问题
     m_threadpool->Producer_add(  recv_task , (void*) ev );
}

void* Block_Epoll_Net::recv_task(void* arg)
{
    myevent_s * ev = (myevent_s*)arg;
    //利用全局指针 方便操作
    Block_Epoll_Net * pthis = ev->pNet;

    //接收和处理分离
    int nRelReadNum = 0;
    int nPackSize = 0;
    char *pSzBuf = NULL;
    do
    {
        nRelReadNum = SSL_read(ev->ssl,&nPackSize,sizeof(nPackSize) );
        if(nRelReadNum <= 0)
            break;

        pSzBuf = new char[nPackSize];
        int nOffSet = 0;
        nRelReadNum = 0;
        //接收包的数据
        while(nPackSize)
        {
            nRelReadNum = SSL_read(ev->ssl,pSzBuf+nOffSet,nPackSize);
            if(nRelReadNum <= 0)
                break;

            nOffSet += nRelReadNum;
            nPackSize -= nRelReadNum;
        }
        //接收和处理分离 跑线程池里其他线程处理 , 避免处理影响接收
        DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd , pSzBuf , nOffSet );
        pthis->m_threadpool->Producer_add(  Buffer_Deal , (void*) buffer );

        // 这次接收完 要重新注册事件  此时 EPOLL MODE -> EPOLLIN|EPOLLONESHOT 没有修改, 使用重复值
        ev->eventadd(  ev->events );

        return 0;

    }while(0);

// 借助 do..while 在最后统一处理错误  避免使用goto语句
    ev->eventdel();
    close(ev->fd);
    //回收event结构
    //pthis->m_mapSockfdToEvent.erase( ev->fd );
    pthis->m_mapSockfdToEvent.erase( ev->fd );
    delete ev;
    return NULL;

}

void * Block_Epoll_Net::Buffer_Deal( void * arg )
{
    DataBuffer * buffer = (DataBuffer *)arg;
    if( !buffer ) return NULL;

    buffer->pNet->m_recv_callback(buffer->sockfd,buffer->buf,buffer->nlen);

 //   printf("pszbuf = %p \n",buffer->buf);
    if(buffer->buf != NULL)
    {
        delete [] buffer->buf;
        buffer->buf = NULL;
    }
    delete buffer;
    return 0;
}

void Block_Epoll_Net::epollout_event( myevent_s *ev )
{
    // epoll LT模式 阻塞模式 发送阻塞 , 不用监听EPOLLOUT事件
}



int Block_Epoll_Net::SendData(int fd, char *szbuf, int nlen)
{
    // 发送不可分割 避免多线程并发
    // 先包大小, 再数据包 , 一次放入缓冲区

    /*
     +--------------+------------------+---------------------+
     |<-- 4bytes -->|<-- 4bytes协议头 ->|<--  协议其他内容    ->|
     +--------------+------------------+---------------------+
     |<- packsize ->|<------------ 数据包 struct ------------>|
     * */

    int nPackSize = nlen + 4;
    vector<char> vecbuf( nPackSize , 0);
    //vecbuf.resize( nPackSize );

    char* buf = &* vecbuf.begin();
    char* tmp = buf;
    *(int*)tmp = nlen;//按四个字节int写入
    tmp += sizeof(int );
    memcpy( tmp , szbuf , nlen );
    SSL* ssl;
    m_mapSocketToSSL.find(fd, ssl);
    int res=0;
    //int res = send(fd,(const char*)buf,nPackSize,MSG_NOSIGNAL);
    if(ssl){
        res = SSL_write( ssl,(const char *)buf, nPackSize);
    }
    return res;
}

void Block_Epoll_Net::setNonBlockFd(int fd)
{
    int flags = 0;
    flags = fcntl(fd, F_GETFL, 0);
    int ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
    if( ret == -1)
        perror("setNonBlockFd fail:");
}

void Block_Epoll_Net::setRecvBufSize( int fd)
{
    //接收缓冲区
    int nRecvBuf = 256*1024;//设置为 256 K
    setsockopt(fd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
}

void Block_Epoll_Net::setSendBufSize( int fd)
{
    //发送缓冲区
    int nSendBuf=128*1024;//设置为 128 K
    setsockopt(fd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
}

#include<netinet/tcp.h>
void Block_Epoll_Net::setNoDelay( int fd)
{
    //nodelay
    int value = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY ,(char *)&value, sizeof(int));
}
