#include"TcpClientNetMediator.h"
#include"../INet/TcpClientNet.h"

TcpClientNetMediator::~TcpClientNetMediator()
{
    //CloseNet();
}

bool TcpClientNetMediator::OpenNet()
{
    m_pNet=new TcpClientNet(this);
    if(m_pNet->InitNet()){
        cout<<"start Net fail"<<endl;
        return true;
    }
    else{
        cout<<"start Net success"<<endl;
        return false;
    }
}

bool TcpClientNetMediator::SendData(long lSendIp, char *buf, int nLen)
{

    Q_UNUSED(lSendIp);
    char* buffer = new char[nLen + sizeof(int)];
    char* tmp = buffer;
    *(int*)tmp = nLen;
    tmp+=sizeof(int);
    memcpy(tmp,buf,nLen);
    m_pNet->sendData(NULL,buffer,nLen+sizeof(int));
    delete []buffer;
    buffer = nullptr;
    return false;


//    Q_UNUSED(lSendIp);
//    m_pNet->sendData(NULL, (char*)&nLen, sizeof(int));
//    m_pNet->sendData(NULL,buf,nLen);
//    return false;
}

void TcpClientNetMediator::CloseNet()
{
    if(m_pNet){
        delete m_pNet;
        m_pNet = nullptr;
    }
}
void TcpClientNetMediator::DealData(long lSendip, char *buf, int nLen)
{
    cout<<__func__<<endl;
    //将收到的数据发给kernel
    Kernel::m_pKernel->dealReadyData(lSendip,buf,nLen);
}
