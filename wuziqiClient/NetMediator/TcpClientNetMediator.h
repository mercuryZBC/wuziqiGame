#pragma once
#include"INetMediator.h"
#include"Kernel/Kernel.h"


class TcpClientNetMediator:public INetMediator{


    // INetMediator interface
public:
    ~TcpClientNetMediator();
    bool OpenNet() override;
    bool SendData(long lSendIp, char *buf, int nLen) override;
    void CloseNet() override;
    void DealData(long lSendip, char *buf, int nLen) override;
};
