#include "clogic.h"
#include "TCPKernel.h"
#include "packdef.h"
#include <cstring>
#include <fstream>
#include <istream>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <utility>
#include <vector>
#include <dirent.h>
#include "GameRoom.h"
#define _DEF_COUT_FUNC_    cout << "clientfd: "<< sock <<" "<< __func__ << endl;
vector<string> split(const string str, const string& delim = " ") {
	vector<string> res;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型  
	char* strs = new char[str.length() + 1]; //不要忘了  
	strcpy(strs, str.c_str());

	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char* p = strtok(strs, d);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型  
		res.push_back(s); //存入结果数组  
		p = strtok(NULL, d);
	}

	return res;
}


void CLogic::setNetPackMap()
{
	NetPackMap(_DEF_TCP_PROTO_LOGIN_RQ) = &CLogic::dealLoginRequest;
	NetPackMap(_DEF_TCP_PROTO_FRIENDINFO_RQ) = &CLogic::dealFriendInfoRequest;
	NetPackMap(_DEF_TCP_PROTO_CREATE_ROOM_RQ) = &CLogic::dealCreateRoomRequest;
	NetPackMap(_DEF_TCP_PROTO_OFFLINE_RQ) = &CLogic::dealClientOffLine;
	NetPackMap(_DEF_TCP_PROTO_PLAYER_EXIT_ROOM) = &CLogic::dealPlayerExitRoom;
	NetPackMap(_DEF_TCP_PROTO_PLAYER_CHESS) = &CLogic::dealPlayerChess;
	NetPackMap(_DEF_TCP_PROTO_JOIN_ROOM) = &CLogic::dealJoinRoomRequest;
	NetPackMap(_DEF_TCP_PROTO_GAME_READY) = &CLogic::playerIsReady;
	NetPackMap(_DEF_TCP_PROTO_LOAD_EXIST_ROOM_RQ) = &CLogic::dealLoadExistRoomRequest;
}

string CLogic::getUserIdUseSock(sock_fd sock)
{
	string userId = "";
	if (m_mapSOCKETtoUserId.IsExist(sock)) {
		m_mapSOCKETtoUserId.find(sock, userId);
	}
	return userId;
}

sock_fd CLogic::getSockUseUserId(string userId)
{
	sock_fd sock = -1;
	if (m_mapUserIdtoSOCKET.IsExist(userId)) {
		m_mapUserIdtoSOCKET.find(userId, sock);
	}
	else {
		printf("sock is not exist\n");
	}
	return sock;
}

void CLogic::dealClientOffLine(sock_fd sock, char* packet, int nlen)
{
	_DEF_COUT_FUNC_
	string userId;
	if(m_mapSOCKETtoUserId.IsExist(sock)){
		m_mapSOCKETtoUserId.find(sock, userId);
		m_mapSOCKETtoUserId.erase(sock);
	}
	if(m_mapUserIdtoSOCKET.IsExist(userId)) m_mapUserIdtoSOCKET.erase(userId);
}

void CLogic::dealLoginRequest(sock_fd sock, char* packet, int nlen)
{
	_DEF_COUT_FUNC_
	STRU_LOGIN_RQ loginPacket = *(STRU_LOGIN_RQ*)packet;
	string userId = loginPacket.userId;
	string sql = "select passwd,userName,iconId,feeling from UserInfo where userId = \"" + userId + "\";";
	cout << sql << endl;
	list<string>selectRes;
	int iResult = m_sql->SelectMySql((char*)sql.c_str(), 4, selectRes);
	if (!iResult) {
		cout << "select Failed" << endl;
		exit(0);
	}

	auto ite = selectRes.begin();

	STRU_LOGIN_RS loginRsPack;
	memset(loginRsPack.userName, 0, sizeof(loginRsPack.userName));
	memset(loginRsPack.feeling, 0, sizeof(loginRsPack.feeling));
	loginRsPack.type = _DEF_TCP_PROTO_LOGIN_RS;

	if (selectRes.size() < 4) {

		cout << "dealLoginRequest::use not exit" << endl;
		loginRsPack.state = userIdOrpasswdError;

	}
	else {
		bool isOnline = 0;
		if (m_mapUserIdtoSOCKET.IsExist(userId)) {
			STRU_KEEP_ALIVE keepAlive;
			int curSock;
			m_mapUserIdtoSOCKET.find(userId, curSock);
			if(curSock == sock){
				isOnline = 0;
			}
			else{
				m_pKernel->SendData(curSock, (char*)&keepAlive, sizeof(keepAlive));
				int res =m_pKernel->SendData(curSock, (char*)&keepAlive, sizeof(keepAlive));
				if(res < 0 ){
					isOnline = 0;
					dealClientOffLine(curSock, nullptr, 0);
				}else{
					loginRsPack.state = userIsOnline;
					isOnline = 1;
				}
			}
		}
		if (isOnline == 0) {
			loginRsPack.state = LoginSuccess;
			//将sock和userid对存入list
			m_mapSOCKETtoUserId.insert(sock, userId);
			m_mapUserIdtoSOCKET.insert(userId, sock);
			ite++;
			//存入用户名
			string userName = *(ite++);
			int nLen = userName.length();
			strncpy(loginRsPack.userName, userName.c_str(), nLen);
			//存入头像id
			loginRsPack.iconId = atoi((*ite++).c_str());
			cout << "dealLoginRequest::success" << endl;

			//存入个人简介
			string feeling = *(ite);
			nLen = feeling.length();
			strncpy(loginRsPack.feeling, feeling.c_str(), nLen);
			//向其他已在线好友发送上线通知
			sendOnlineInfo(loginPacket.userId);
		}
	}

	m_pKernel->SendData(sock, (char*)&loginRsPack, sizeof(loginRsPack));//返回登录请求结果
}

void CLogic::dealFriendInfoRequest(sock_fd sock, char* packet, int nlen)
{
	_DEF_COUT_FUNC_
	string strUserId;
	if(m_mapSOCKETtoUserId.IsExist(sock)){//通过sock查找userid
		m_mapSOCKETtoUserId.find(sock, strUserId);
	}else{
		return;
	}
	string sql = +"select friendId from friend where userId = \"" + strUserId + "\";";
	cout << sql << endl;
	list<string>selectRes;
	int iResult = m_sql->SelectMySql((char*)sql.c_str(), 1, selectRes);
	if (!iResult) {
		cout << "select Failed" << endl;
		exit(0);
	}


	auto ite = selectRes.begin();
	while (ite != selectRes.end()) {
		cout << "returnFriendInfo FriendId:" << *ite << endl;
		STRU_FRIENDINFO_RS friendInfo=getFriendInfo(*ite);
		m_pKernel->SendData(sock, (char*)&friendInfo, sizeof(friendInfo));
		ite++;
	}
	sendOnlineInfo((char*)strUserId.c_str());
}

void CLogic::dealCreateRoomRequest(sock_fd sock, char* packet, int nlen)
{
	_DEF_COUT_FUNC_
	STRU_CREATE_ROOM_RQ createRoomRq = *(STRU_CREATE_ROOM_RQ*)packet;
	GameRoom* gameRoom = new GameRoom(createRoomRq.userId,this);
	int num = -1;
	//m_pLockRoomVec->lock();
	for (int i = 0; i < m_vecIsGameRoomExist.size(); i++) {
		if (m_vecIsGameRoomExist[i] == false) {
			m_vecIsGameRoomExist[i] = true;
			num = i;
			break;
		}
	}
	if (num == -1) {
		m_vecIsGameRoomExist.push_back(true);
		num = m_vecIsGameRoomExist.size() - 1;
	}
	//m_pLockRoomVec->unlock();
	//m_pLockRoomMap->lock();
	if (!m_mapRoomNumToGameRoom.count(num)) {
		m_mapRoomNumToGameRoom[num] = gameRoom;
	}
	//m_pLockRoomMap->unlock();
	STRU_CREATE_ROOM_RS createRoomRs;
	createRoomRs.roompack = getRoomInfo(num);
	m_pKernel->SendData(sock, (char*)&createRoomRs, sizeof(createRoomRs));
	sendRoomInfo();
}

void CLogic::dealLoadExistRoomRequest(sock_fd sock, char* packet, int nlen)
{
	cout << "Kernel::dealLoadExistRoomRequest" << endl;
	sendRoomInfo(sock);
}

void CLogic::dealPlayerExitRoom(sock_fd sock, char* packet, int nlen)
{
	_DEF_COUT_FUNC_
	STRU_PLAYER_EXIT_ROOM playerExitRoom = *(STRU_PLAYER_EXIT_ROOM*)packet;
	cout << "Kernel::dealPlayerExitRoom" << endl;
	int roomId = playerExitRoom.roomId;
	string userId;
	if (m_mapSOCKETtoUserId.IsExist(sock)) {
		userId = m_mapSOCKETtoUserId[sock];
		m_mapSOCKETtoUserId.find(sock, userId);
	}
	if (m_mapRoomNumToGameRoom.count(roomId)) {
		GameRoom* gm = m_mapRoomNumToGameRoom[roomId];
		int userCount=0;
		if (gm->m_userIsExist1) {
			userCount++;
			if (gm->m_userId1 == userId) {
				gm->m_userId1 = "";
				gm->m_userIsExist1 = false;
			}
		}
		if (gm->m_userIsExist2) {
			userCount++;
			if (gm->m_userId2 == userId) {
				gm->m_userId2 = "";
				gm->m_userIsExist2 = false;
			}
		}
		if (userCount == 1) {
			delete gm;
			gm = nullptr;
			m_mapRoomNumToGameRoom.erase(m_mapRoomNumToGameRoom.find(roomId));
			m_vecIsGameRoomExist[roomId] = 0;
			STRU_ROOM_CLOSE roomClosePack;
			roomClosePack.roomId = roomId;
			vector<pair<int,string>>vec;
			m_mapSOCKETtoUserId.getAll(vec);
			for(int i=0;i<vec.size();i++){
				m_pKernel->SendData(vec[i].first, (char*)&roomClosePack, sizeof(STRU_ROOM_CLOSE));
			}
		}
		sendRoomInfo();
	}
}

void CLogic::playerExitRoom(string userId)
{
	
	GameRoom* gm;
	for (int i = 0; i < m_vecIsGameRoomExist.size(); i++) {
		if (m_vecIsGameRoomExist[i] == true) {
			gm = m_mapRoomNumToGameRoom[i];
			int userCount = 0;
			int flag = false;
			if (gm->m_userIsExist1) {
				userCount++;
				if (gm->m_userId1 == userId) {
					flag = true;
					gm->m_userId1 = "";
					gm->m_userIsExist1 = false;
				}
			}
			if (gm->m_userIsExist2) {
				userCount++;
				if (gm->m_userId2 == userId) {
					flag = true;
					gm->m_userId2 = "";
					gm->m_userIsExist2 = false;
				}
			}
			if (!flag) continue;
			if (userCount == 1) {
				delete gm;
				gm = nullptr;
				m_mapRoomNumToGameRoom.erase(m_mapRoomNumToGameRoom.find(i));
				m_vecIsGameRoomExist[i] = false;
				STRU_ROOM_CLOSE roomClosePack;
				roomClosePack.roomId = i;
				vector<pair<int,string>>vec;
				m_mapSOCKETtoUserId.getAll(vec);
				for(int i=0;i<vec.size();i++){
					m_pKernel->SendData(vec[i].first, (char*)&roomClosePack, sizeof(STRU_ROOM_CLOSE));
				}

			}
		}
	}
	sendRoomInfo();
}

void CLogic::dealJoinRoomRequest(sock_fd sock, char* packet, int nlen)
{
	STRU_JOIN_ROOM_RS joinRoomRs;
	STRU_JOIN_ROOM joinRoomRq = *(STRU_JOIN_ROOM*)packet;
	int roomId = joinRoomRq.roomId;
	if (m_mapRoomNumToGameRoom[roomId]) {
		GameRoom* gm = m_mapRoomNumToGameRoom[roomId];
		string userId = getUserIdUseSock(sock);
		if (userId == "") {
			joinRoomRs.state = joinError;
		}
		else {
			int res = gm->addPlayer(userId);
			if (res) {
				joinRoomRs.state = joinSuccess;
				joinRoomRs.roompack = getRoomInfo(roomId);
			}
			else {
				joinRoomRs.state = playerExist;
			}
		}
	}
	else {
		joinRoomRs.state = roomIsNotExist;
	}
	m_pKernel->SendData(sock, (char*)&joinRoomRs, sizeof(joinRoomRs));
	sendRoomInfo();
}

void CLogic::playerIsReady(sock_fd sock, char* packet, int nlen)
{
	STRU_GAME_READY gameReadyPack = *(STRU_GAME_READY*)packet;
	string userId = getUserIdUseSock(sock);
	int roomId = gameReadyPack.roomId;
	if (m_mapRoomNumToGameRoom.count(roomId)) {
		GameRoom* gm = m_mapRoomNumToGameRoom[roomId];
		gm->playerReady(userId);
	}
}

void CLogic::dealPlayerChess(sock_fd sock, char* packet, int nlen)
{
	STRU_PLAYER_CHESS playerChess = *(STRU_PLAYER_CHESS*)packet;
	if (m_mapRoomNumToGameRoom.count(playerChess.roomId)) {
		m_mapRoomNumToGameRoom[playerChess.roomId]->playerChess(playerChess);
	}
}

void CLogic::sendOnlineInfo(char* userId)
{
	string strUserId = userId;
	string sql = +"select friendId from friend where userId = \"" + strUserId + "\";";
	cout << sql << endl;
	list<string>selectRes;
	int iResult = m_sql->SelectMySql((char*)sql.c_str(), 1, selectRes);
	if (!iResult) {
		cout << "select Failed" << endl;
		exit(0);
	}
	auto ite = selectRes.begin();
	while (ite != selectRes.end()) {
		//判断好友是否在线
		//if (*ite == userId) {//当前好友的id为自己的id，则continue;
		//	ite++;
		//	continue;
		//}
		vector<pair<sock_fd, string>>m_listUserOnlineSocketAnduserId;
		m_mapSOCKETtoUserId.getAll(m_listUserOnlineSocketAnduserId);
		for (auto var : m_listUserOnlineSocketAnduserId) {
			if (var.second == *ite) {//好友在线
				STRU_FRIEND_ONLINE friendOnlineInfo;

				memset(friendOnlineInfo.friendId, 0, sizeof(friendOnlineInfo.friendId));

				int nLen = sizeof(friendOnlineInfo);

				strncpy(friendOnlineInfo.friendId, userId, strlen(userId));
				m_pKernel->SendData(var.first, (char*)&friendOnlineInfo, nLen);//发送
			}
		}
		ite++;
	}
}

void CLogic::sendRoomInfo(sock_fd sock)
{
	_DEF_COUT_FUNC_
	STRU_LOAD_EXIST_ROOM_RS loadExistRoomRs;
	for (auto ite : m_mapRoomNumToGameRoom) {
		loadExistRoomRs = getRoomInfo(ite.first);
		m_pKernel->SendData(sock, (char*)&loadExistRoomRs, sizeof(loadExistRoomRs));
	}
}

void CLogic::sendRoomInfo()
{
	
	vector<pair<string,sock_fd>>vec;
	m_mapUserIdtoSOCKET.getAll(vec);
	for(int i=0;i<vec.size();i++){
		sendRoomInfo(vec[i].second);
	}
}

int CLogic::getIconId(string userId)
{
	cout<<"CLogic::getIconId"<<endl;
	string sql = "select iconId from userinfo where userid =\"" + userId + "\";";
	cout << sql << endl;
	list<string>selectRes;
	int iResult = m_sql->SelectMySql((char*)sql.c_str(), 1, selectRes);
	if (!iResult) {
		cout << "select Failed" << endl;
		exit(0);
	}
	int iconId = atoi(selectRes.front().c_str());
	return iconId;
}

STRU_FRIENDINFO_RS CLogic::getFriendInfo(string friendId)
{
	cout<<"CLogic::getFriendInfo"<<endl;
	string sql = +"select userId,userName,iconId,feeling from UserInfo where userId = \"" + friendId + "\";";
	STRU_FRIENDINFO_RS friendInfo;
	cout << sql << endl;
	memset(friendInfo.userId, 0, sizeof(friendInfo.userId));
	memset(friendInfo.userName, 0, sizeof(friendInfo.userName));
	memset(friendInfo.feeling, 0, sizeof(friendInfo.feeling));
	list<string>selectRes;

	int iResult = m_sql->SelectMySql((char*)sql.c_str(), 4, selectRes);

	if (!iResult) {
		cout << "select Failed" << endl;
		exit(0);
	}
	if (selectRes.size() < 4) {

		cout << "FriendInfo::friend not exit" << endl;

	}
	else {
		auto ite1 = selectRes.begin();
		string friendId = *(ite1++);//保存好友id
		int nLen = friendId.length();
		strncpy(friendInfo.userId, friendId.c_str(), nLen);


		friendInfo.state = offline;
		if (m_mapUserIdtoSOCKET.IsExist(friendId)) {
			friendInfo.state = online;
		}

		string friendName = *(ite1++);//保存好友name
		nLen = friendName.length();
		strncpy(friendInfo.userName, friendName.c_str(), nLen);



		int iconId = atoi((*ite1++).c_str());//保存好友头像id
		friendInfo.iconId = iconId;



		string feeling = *(ite1++);//保存好友feeling
		nLen = feeling.length();
		strncpy(friendInfo.feeling, feeling.c_str(), nLen);
	}
	return friendInfo;
}

STRU_LOAD_EXIST_ROOM_RS CLogic::getRoomInfo(int roomId)
{
	STRU_LOAD_EXIST_ROOM_RS loadExistRoomRs;
	GameRoom gm = *m_mapRoomNumToGameRoom[roomId];
	loadExistRoomRs.roomId = roomId;
	loadExistRoomRs.PlayerNum = gm.m_userIsExist1 + gm.m_userIsExist2;
	loadExistRoomRs.isLock = gm.m_isLock;
	loadExistRoomRs.user1Exist = gm.m_userIsExist1;
	loadExistRoomRs.user2Exist = gm.m_userIsExist2;
	if (gm.m_userIsExist1) {
		strncpy(loadExistRoomRs.user1Id, gm.m_userId1.c_str(), gm.m_userId1.length());
		loadExistRoomRs.user1IconId = getIconId(gm.m_userId1);
	}
	if (gm.m_userIsExist2) {
		strncpy(loadExistRoomRs.user2Id, gm.m_userId2.c_str(), gm.m_userId2.length());
		loadExistRoomRs.user2IconId = getIconId(gm.m_userId2);
	}
	return loadExistRoomRs;
}


