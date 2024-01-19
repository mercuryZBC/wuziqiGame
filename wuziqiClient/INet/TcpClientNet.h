#pragma once
#include "INet.h"
#include<QString>
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
    void loadIniFile();
protected:
    QString m_ip;
    QString m_port;
    void recvData() override;
    //接收消息线程
    HANDLE m_handle;
    static unsigned __stdcall RecvThread(void* lpVoid);

};
