#include"TcpClientNet.h"
#include"Config/config.h"
#include<process.h>
#include"../NetMediator/TcpClientNetMediator.h"
#include<QCoreApplication>
#include<QSettings>
#include<QFileInfo>
TcpClientNet::TcpClientNet(INetMediator* netMediator):m_sock(NULL),m_isStop(0)
{
    m_pMediator=netMediator;
    m_ip = "182.92.101.102";
    m_port="12345";
    loadIniFile();
}

TcpClientNet::~TcpClientNet()
{
    UninitNet();
}

bool TcpClientNet::InitNet()
{
    //加载库
        WORD wVersionRequested;
        WSADATA wsaData;
        int err;

        /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
        wVersionRequested = MAKEWORD(2, 2);

        err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0) {
            /* Tell the user that we could not find a usable */
            /* Winsock DLL.                                  */
            printf("WSAStartup failed with error: %d\n", err);
            return 1;
        }

        /* Confirm that the WinSock DLL supports 2.2.*/
        /* Note that if the DLL supports versions greater    */
        /* than 2.2 in addition to 2.2, it will still return */
        /* 2.2 in wVersion since that is the version we      */
        /* requested.                                        */

        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            /* Tell the user that we could not find a usable */
            /* WinSock DLL.                                  */
            printf("Could not find a usable version of Winsock.dll\n");
            WSACleanup();
            return 1;
        }
        else {
            printf("The Winsock 2.2 dll was found okay\n");
        }
        //创建套接字

        m_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (INVALID_SOCKET == m_sock) {
            cout << "sock error" << WSAGetLastError() << endl;
            WSACleanup();
        }
        else {
            cout << "socket create success" << endl;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family=AF_INET;
        serverAddr.sin_addr.S_un.S_addr=inet_addr(m_ip.toStdString().c_str());
        serverAddr.sin_port=htons(m_port.toUShort());

        if (connect(m_sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
               closesocket(m_sock);
               printf("Unable to connect to server: %ld\n", WSAGetLastError());
               WSACleanup();
               return 1;
        }
       else {
           printf("connect suuccess\n");
       }


       unsigned int threadId=0;//线程id
       //创建接收数据的线程
       m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0,&threadId);
        return false;
}

bool TcpClientNet::sendData(long lsendIp, char *buf, int nLen)
{
    Q_UNUSED(lsendIp)
    printf("TcpClientNet::sendData\n");
    int iResult=send(m_sock, buf, nLen, 0);
        //发送失败
        if (iResult == SOCKET_ERROR) {

            cout << "TcpServerNet::sendData:" << WSAGetLastError() << endl;

            closesocket(m_sock);

            WSACleanup();

            return true;
        }
        return false;
}

void TcpClientNet::UninitNet()
{
    closesocket(m_sock);
    m_isStop=1;
    if(m_pMediator){
        delete m_pMediator;
        m_pMediator=nullptr;
    }


}

void TcpClientNet::loadIniFile()
{
    //获取exe目录
    QString path = QCoreApplication::applicationDirPath()+"/config.ini";
    QFileInfo info(path);
    QSettings setting(path,QSettings::IniFormat);
    if(info.exists()){
        setting.beginGroup("net");
        QVariant strIp = setting.value("ip","");
        QVariant strPort = setting.value("port","");
        if(!strIp.toString().isEmpty()){
            m_ip = strIp.toString();
        }
        if(!strPort.toString().isEmpty()){
            m_port = strPort.toString();
        }
        setting.endGroup();
    }else{
        //打开组
        setting.beginGroup("net");
        setting.setValue("ip",m_ip);
        setting.setValue("port",m_port);
        setting.endGroup();
    }
}

void TcpClientNet::recvData()
{
    //cout << "TcpClientNet::recvData" << endl;
    Sleep(10);//因为线程是创建即运行，所以需要等当前sock和handle放入Map再运行


    int nRecvNum=0;
    int packLen=0;//包长度

    while (!m_isStop) {
        nRecvNum = recv(m_sock, (char*)&packLen, sizeof(int), 0);
        cout<<packLen<<endl;
        if (nRecvNum >0) {

            //定义包长度大小的缓冲区
            char* recvBuf = new char[packLen];
            memset(recvBuf, 0, packLen*sizeof(char));
            //设置偏移量
            int offset = 0;
            int notRecvLen=packLen;//剩余未接收的长度
            //接收包数据
            while (notRecvLen>0) {
                notRecvLen -= recv(m_sock, recvBuf + offset, notRecvLen, 0);

                offset = packLen - notRecvLen;
            }
            //cout<<"TcpClientNet::dataComing packetsize = "<<packLen<<endl;
            //把包数据传给mediator
            m_pMediator->DealData(NULL,recvBuf,packLen);
            if(recvBuf){
                delete[] recvBuf;
                recvBuf=nullptr;
            }

        }
        else if (0 == nRecvNum || 10054 == WSAGetLastError()) {
            cout << "TcpClientNet::recvData close connection" << endl;
            break;
        }
        else {
            cout << "TcpClientNet::RecvData error" << WSAGetLastError() << endl;
        }
    }
    return;
}

unsigned TcpClientNet::RecvThread(void *lpVoid)
{
    TcpClientNet* pThis=(TcpClientNet*)lpVoid;
    pThis->recvData();

}
