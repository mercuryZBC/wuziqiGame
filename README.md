# wiziqiGame

## 介绍

该项目是一款在线棋牌对战平台，已实现用户登录、注册、游戏下载、游戏删除。内置在线五子棋游戏，并实现创建房间，加入房间，快速匹配，好友对战，掉线重连，人机对战等功能。

## 功能截图

游戏下载
![OyU8fF.png](https://ooo.0x0.ooo/2024/02/21/OyU8fF.png)

启动游戏

![OyU6pD.png](https://ooo.0x0.ooo/2024/02/21/OyU6pD.png)

![image-20240113134650576](https://s2.loli.net/2024/01/13/6xXhBCUjMrIJgy2.png)

在线游戏大厅界面

![image-20240113140156963](https://s2.loli.net/2024/01/13/x5aCuDthslHbyWq.png)

对局准备界面

![image-20240113140230264](https://s2.loli.net/2024/01/13/mcUGhMvRbfgpC7q.png)

对局结束界面

![image-20240113140319320](https://s2.loli.net/2024/01/13/onGpsuwBd2NDTv5.png)

## 软件架构

C/S架构，客户端采用qt开发GUI界面，服务端在linux平台开发

### UML类图分析

#### 1. 网络接口类

![image.png](https://cdn.nlark.com/yuque/0/2024/png/42406148/1705895737385-4cc2796a-6864-40be-ba71-824b9290a1ac.png#averageHue=%231b1720&clientId=uc1437574-ac05-4&from=paste&height=799&id=uedd9b72b&originHeight=1199&originWidth=1646&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=199835&status=done&style=none&taskId=u441ff0d7-3186-4f9e-9c1f-e705a387bfa&title=&width=1097.3333333333333)

2. 逻辑处理类Kernel

   ![image.png](https://cdn.nlark.com/yuque/0/2024/png/42406148/1705895764607-adcd9e01-edd5-4384-9902-07b04ea7dd8b.png#averageHue=%231b1822&clientId=uc1437574-ac05-4&from=paste&height=638&id=u89d58525&originHeight=957&originWidth=1052&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=237222&status=done&style=none&taskId=ue9c26056-0432-421c-8fae-87350997f7f&title=&width=701.3333333333334)

    3.图形界面类



## 服务端结构

服务器采用基于epoll监听的Reactor模式处理客户端请求

Reactor主要由Reactor 线程`、`Handlers 处理器组成，Reactor线程负责监听客户端请求，通过执行epoll_wait判断客户端事件是否到达，如果有事件到达，将该事件绑定到一个Handler处理器，则将该任务放入事件队列，线程池的工作者线程从任务队列中获取线程。

![image-20240222231008222](https://s2.loli.net/2024/02/22/7GYrmIlBQf2XeZh.png)

### 1. Reactor 线程

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
                    accept_event();//accept事件
                else
                    recv_event( ev );//客户端业务事件
            }
            if ((events[i].events & EPOLLOUT) ) {
                epollout_event( ev );
            }
        }
    }
}
~~~

### 2.消费者线程

消费者线程进行任务处理

~~~cpp
/* 工作线程函数 消费者*/
void * thread_pool::Custom(void * arg)
{
	// 获取线程池对象指针
    pool_t * p = (pool_t*)arg;
    task_t task;
    while(p->thread_shutdown)  // 线程池未关闭
    {
        pthread_mutex_lock(&p->lock);// 上锁
		// 当前任务队列中没有任务，且线程池未关闭
        while(p->queue_cur == 0 && p->thread_shutdown  )
        {
			// 等待有新的任务被添加到队列中
            pthread_cond_wait(&p->not_empty,&p->lock);
        }
		// 线程池已关闭
        if(!p->thread_shutdown  )
        {
            pthread_mutex_unlock(&p->lock);
            pthread_exit(NULL); // 结束此线程
        }
		// 需要等待关闭的线程数大于零，且当前存活的线程数大于最小线程数
        if(p->thread_wait > 0 && p->thread_alive > p->thread_min)
        {
            --(p->thread_wait); // 等待关闭的线程数减一
            --(p->thread_alive);// 存活的线程数减一
            pthread_mutex_unlock(&p->lock);// 解锁
            pthread_exit(NULL);// 结束此线程
        }
		// 取出任务
        task.task = p->queue_task[p->queue_rear].task;
        task.arg = p->queue_task[p->queue_rear].arg;
        p->queue_rear = (p->queue_rear + 1) % p->queue_max;// 更新队列尾指针
        --(p->queue_cur);// 当前任务队列中的任务数减一
        pthread_cond_signal(&p->not_full); // 通知生产者线程有新的任务可供添加
        ++(p->thread_busy);// 忙碌的线程数加一
        pthread_mutex_unlock(&p->lock);// 解锁
        //执行核心工作
        (*task.task)(task.arg);
        pthread_mutex_lock(&p->lock);// 上锁
        --(p->thread_busy);// 忙碌的线程数减一
        pthread_mutex_unlock(&p->lock); // 解锁
    }
    return 0;
}
~~~

