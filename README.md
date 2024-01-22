# wiziqiGame

## 介绍

wiziqiGame是一款基于tcp的在线五子棋游戏，可以实现玩家对战，人机对战，在线对战。

## 软件架构

C/S架构，客户端采用qt开发GUI界面，服务端在linux平台开发

### UML类图分析

#### 1. 网络接口类

![image.png](https://cdn.nlark.com/yuque/0/2024/png/42406148/1705895737385-4cc2796a-6864-40be-ba71-824b9290a1ac.png#averageHue=%231b1720&clientId=uc1437574-ac05-4&from=paste&height=799&id=uedd9b72b&originHeight=1199&originWidth=1646&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=199835&status=done&style=none&taskId=u441ff0d7-3186-4f9e-9c1f-e705a387bfa&title=&width=1097.3333333333333)

2. 逻辑处理类Kernel

   ![image.png](https://cdn.nlark.com/yuque/0/2024/png/42406148/1705895764607-adcd9e01-edd5-4384-9902-07b04ea7dd8b.png#averageHue=%231b1822&clientId=uc1437574-ac05-4&from=paste&height=638&id=u89d58525&originHeight=957&originWidth=1052&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=237222&status=done&style=none&taskId=ue9c26056-0432-421c-8fae-87350997f7f&title=&width=701.3333333333334)

    3.图形界面类

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

