#pragma once
#include<winsock.h>
#include<iostream>
#include<set>
using namespace std;

//#pragma comment(lib,"Ws2_32.lib")




class INetMediator;
class INet
{
public:
	INet() {}
    virtual ~INet() {}
	//初始化网络
	virtual bool InitNet() = 0;
	//发送数据
	virtual bool sendData(long lsendIp, char* buf, int nLen) = 0;

	//关闭网络
	virtual void UninitNet() = 0;

    //把long类型的ip地址转换成string类型的
    static std::string GetIpString(long ip){
        sockaddr_in sockAddr;
        sockAddr.sin_addr.S_un.S_addr=ip;
        return inet_ntoa(sockAddr.sin_addr);
    }
    //char* std::string,Qstring 转换
    //std::string= char*,QString =char*(char*)是基础数据类型、std::string和Qstring是封装好的类，基础数据类型可以给类直接赋值）
    //std::string调用c_str()转换成char*
    //QString可以调用toStdString转换成std::string

    //获取本地ip地址列表
    static set<long>GetValidIpList(){
        set<long>setIp;
        long ip;
        int i=0;
        //1.获取主机名字
        char nameBuf[100]="";
        gethostname(nameBuf,100);
        //2.根据主机名获取ip地址列表
        struct hostent *remoteHost=gethostbyname(nameBuf);
        while (remoteHost->h_addr_list[i] != 0) {
                       ip = *(u_long *) remoteHost->h_addr_list[i++];
                       setIp.insert(ip);
                   }
        return setIp;
    }
protected:
	//接受数据
	virtual void recvData() = 0;
	//中介者类指针，父类指针指向子类接口
	INetMediator* m_pMediator;
};

