#pragma once
#include<QObject>



class INet;
class INetMediator:public QObject
{
    Q_OBJECT
public:
    INetMediator();
    ~INetMediator();
	//打开网络
	virtual bool OpenNet() = 0;
	//发送数据
	virtual bool SendData(long lSendIp, char* buf, int nLen) = 0;
	//关闭网络
	virtual void CloseNet() = 0;
	//处理数据
    virtual void DealData(long lSendip, char* buf, int nLen) = 0;

protected:
	INet* m_pNet;//网络接口类指针

};

