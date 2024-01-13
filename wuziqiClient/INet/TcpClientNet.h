#pragma once
#include "INet.h"
class TcpClientNet:public INet{
private:
    SOCKET m_sock;
    bool m_isStop;
    // INet interface
public:
    TcpClientNet(INetMediator* netMediator);
    virtual ~TcpClientNet();
    bool InitNet() override;
    bool sendData(long lsendIp, char *buf, int nLen) override;
    void UninitNet() override;

protected:
    void recvData() override;
    //接收消息线程
    HANDLE m_handle;
    static unsigned __stdcall RecvThread(void* lpVoid);

};
