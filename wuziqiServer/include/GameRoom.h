#pragma once
#include<string>
#include"Timer.h"
#include<cstdlib>
#include<ctime>
#include<vector>
#include"packdef.h"
#include "TCPKernel.h"

using namespace std;
class Kernel;
class GameRoom
{
public:
	const int kBoardSizeNum = 15;
	CLogic* m_pLogic;
	string m_userId1;//玩家1  Id
	string m_userId2;//玩家2
	int user1RemainTime = 6000;
	int user2RemainTime = 6000;
	bool m_isStart;//游戏是否开始
	bool m_user1IsReady;
	bool m_user2IsReady;
	bool m_isLock;//是否为私密房间
	string password;//如果为私密房间,设置的密码
	bool m_userIsExist1;//玩家1 是否进入房间
	bool m_userIsExist2;//玩家2 是否进入房间
	bool blackSide;//0代表玩家1为黑色方,1代表玩家2为黑色方
	bool curSide;//0代表玩家1,1代表玩家2
	Timer* m_timer;
	std::vector<std::vector<int>> m_gameMapVec;
	GameRoom(string userId,CLogic* pLogic);
	~GameRoom();
	void startGame();
	void enterRoom(string userId);
	int addPlayer(string userId);
	void playerReady(string userId);
	void playerChess(STRU_PLAYER_CHESS playerChess);
	bool isWin(int row, int col); // 判断游戏是否胜利
	void clearGame();
public:
	void setRemainTime();
private:

};

