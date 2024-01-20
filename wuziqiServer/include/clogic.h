#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"
#include "block_epoll_net.h"
#include <sys/socket.h>
#include <mutex>
#include "GameRoom.h"
struct SERVER_FILE_INFO {
	int fileSize;
	char sendUserId[12];
	char recvUserId[12];
	char fileName[2048];
	char originFileName[2048];
};

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
private:
	mutex* m_pLockRoomVec;
	mutex* m_pLockRoomMap;
public:
    list<pair<sock_fd, string>>m_listUserOnlineSocketAnduserId;//保存socket和userId;
    vector<bool>m_vecIsGameRoomExist;//存放房间号是否被占用
    map<int,GameRoom*>m_mapRoomNumToGameRoom;
    //设置协议映射
    void setNetPackMap();

    /*****************保存用户临时信息******************/
    MyMap<sock_fd, string>m_mapSOCKETtoUserId;
	MyMap<string, sock_fd>m_mapUserIdtoSOCKET;
	//map<int, SERVER_FILE_INFO>m_mapSeqToFileInfo;
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    string getUserIdUseSock(sock_fd sock);
	sock_fd getSockUseUserId(string userId);
	void dealClientOffLine(sock_fd sock, char* packet, int nlen);
	//处理登录请求
	void dealLoginRequest(sock_fd sock, char* packet, int nlen);
	void dealLoginRequestUsePassword(sock_fd sock,char* packet,int nlen);
	//处理注册请求
	void dealRegisterRequest(sock_fd sock, char* packet, int nlen);


	//处理获取好友列表请求
	void dealFriendInfoRequest(sock_fd sock, char* packet, int nlen);//返回好友信息
	//处理创建房间请求
	void dealCreateRoomRequest(sock_fd sock, char* packet, int nlen);
	//处理加载已经存在房间的请求
	void dealLoadExistRoomRequest(sock_fd sock, char* packet, int nlen);
	//有用户退出房间
	void dealPlayerExitRoom(sock_fd sock, char* packet, int nlen);
	void playerExitRoom(string userId);
	void dealJoinRoomRequest(sock_fd sock, char* packet, int nlen);

	void playerIsReady(sock_fd sock, char* packet, int nlen);

	void dealPlayerChess(sock_fd sock, char* packet, int nlen);

public:
	//向其他在线好友发送上线通知
	void sendOnlineInfo(char* userId);
	//发送房间信息
	void sendRoomInfo(sock_fd sock);
	void sendRoomInfo();
public:
	int getIconId(string userId);//通过userId获取头像id
	STRU_FRIENDINFO_RS getFriendInfo(string friendId);
	STRU_LOAD_EXIST_ROOM_RS getRoomInfo(int roomId);//获取用户信息
public:
	TcpKernel* m_pKernel;
private:
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
};



#endif // CLOGIC_H
