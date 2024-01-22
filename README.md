# wiziqiGame

## 介绍

wiziqiGame是一款基于tcp的在线五子棋游戏，可以实现玩家对战，人机对战，在线对战。

## 软件架构

C/S架构，客户端采用qt开发GUI界面，服务端在linux平台开发

### UML类图分析

#### 1. 网络接口类

![image-20240122114302035](https://s2.loli.net/2024/01/22/TXR8uUsEjOPKCGr.png)

2. 逻辑处理类Kernel

   ![image-20240122114451584.png](https://s2.loli.net/2024/01/22/79cz2xvLIb4YoUa.png)

3. 界面处理类

   

## 功能截图

![image-20240113134650576](https://s2.loli.net/2024/01/13/6xXhBCUjMrIJgy2.png)

在线游戏大厅界面

![image-20240113140156963](https://s2.loli.net/2024/01/13/x5aCuDthslHbyWq.png)

对局准备界面

![image-20240113140230264](https://s2.loli.net/2024/01/13/mcUGhMvRbfgpC7q.png)

对局结束界面

![image-20240113140319320](https://s2.loli.net/2024/01/13/onGpsuwBd2NDTv5.png)

## 服务端讲解

### 1. epoll事件监听

~~~cpp
//事件监听循环代码
void Block_Epoll_Net::EventLoop()
{
    printf("EventLoop:server running\n");
    int  i = 0;
    while (1) {
        /* 等待事件发生 */
        int nfd = epoll_wait( m_epoll_fd, events, MAX_EVENTS+1, 1000);
        if (nfd < 0) {
            printf("epoll_wait error, exit\n");
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
~~~

