#pragma once
#include "INet.h"
#include<QString>

#include "openssl/ssl.h"
#include "openssl/err.h"

class TcpClientNet:public INet{
private:
    SOCKET m_sock;
    bool m_isStop;
    // INet interface
public:
    TcpClientNet(INetMediator* netMediator);
    virtual ~TcpClientNet();
    bool sslInit();
    bool setsslSocket();
    void sslUninit();
    bool InitNet() override;
    bool sendData(long lsendIp, char *buf, int nLen) override;
    void UninitNet() override;
    void loadIniFile();
protected:
    SSL_CTX *m_ctx;
    SSL *m_ssl;
    QString m_ip;
    QString m_port;
    void recvData() override;
    //接收消息线程
    HANDLE m_handle;
    static unsigned __stdcall RecvThread(void* lpVoid);

};
