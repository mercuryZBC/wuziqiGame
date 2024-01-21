#include"GameRoom.h"
#include "clogic.h"
#include<iostream>
using namespace std;
GameRoom::GameRoom(string userId,CLogic* pLogic)
{
	m_isStart = false;
	srand(time(0));
	m_isLock = false;
	m_pLogic = pLogic;
	m_userIsExist1 = true;
	m_userId1 = userId;
	m_userIsExist2 = false;
	m_timer = new Timer;
	m_user1IsReady = false;
	m_user2IsReady = false;
	m_gameMapVec = vector<vector<int>>(15,vector<int>(kBoardSizeNum, 0));//初始化棋盘
}

GameRoom::~GameRoom()
{
	m_isStart = false;
	/*if (m_timer) delete m_timer;
	m_timer = nullptr;*/
	m_timer->stop();
}



void GameRoom::startGame()
{
	m_isStart = true;
	m_gameMapVec.resize(15, vector<int>(kBoardSizeNum, 0));
	blackSide = rand() % 2;//随机选的黑色方
	curSide = blackSide;
	STRU_GAME_STRAT gameStartPack;
	gameStartPack.remainTime = 6000;
	gameStartPack.user1isBlack = curSide;
	m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&gameStartPack, sizeof(gameStartPack));
	gameStartPack.user1isBlack = curSide;
	m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&gameStartPack, sizeof(gameStartPack));
	//m_timer->start(100,std::bind(&GameRoom::setRemainTime,this));
}

void GameRoom::enterRoom(string userId)
{
	if(m_userIsExist1) {
		m_userIsExist2 = true;
		m_userId2 = userId;
	}
	else {
		m_userIsExist1 = true;
		m_userId1 = userId;
	}
}

int GameRoom::addPlayer(string userId)
{
	if (!m_userIsExist1) {
		m_userIsExist1 = true;
		m_userId1 = userId;
		
		return 1;//加入房间成功
	}
	else if (!m_userIsExist2) {
		m_userIsExist2 = true;
		m_userId2 = userId;
		return 2;
	}
	else {
		return 0;
	}
	
}

void GameRoom::playerReady(string userId)
{
	if (m_userId1 == userId) {
		m_user1IsReady = true;
	}
	else if (m_userId2 == userId) {
		m_user2IsReady = true;
	}
	if (m_user1IsReady && m_user2IsReady) {
		startGame();
	}
}

void GameRoom::playerChess(STRU_PLAYER_CHESS playerChess)
{
	cout << "GameRoom::playerChess" << endl;
	if (playerChess.side) {//黑色方chess
		m_gameMapVec[playerChess.chessRow][playerChess.chessCol] = 1;
	}
	else {//白色方chess
		m_gameMapVec[playerChess.chessRow][playerChess.chessCol] = -1;
	}
	if (curSide == 0) {
		m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&playerChess, sizeof(playerChess));
	}
	else {
		m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&playerChess, sizeof(playerChess));
	}
	curSide = !curSide;
	bool win = isWin(playerChess.chessRow, playerChess.chessCol);
	if (win) {
		m_isStart =false;
		STRU_GAME_OVER gameOver;
		gameOver.winSide = playerChess.side;
		m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&gameOver, sizeof(gameOver));
		m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&gameOver, sizeof(gameOver));
		m_user1IsReady = false;
		m_user2IsReady = false;
		clearGame();
	}
}



bool GameRoom::isWin(int row, int col)
{
	// 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
	// 水平方向
	for (int i = 0; i < 5; i++)
	{
		// 往左5个，往右匹配4个子，20种情况
		if (col - i > 0 &&
			col - i + 4 < kBoardSizeNum &&
			m_gameMapVec[row][col - i] == m_gameMapVec[row][col - i + 1] &&
			m_gameMapVec[row][col - i] == m_gameMapVec[row][col - i + 2] &&
			m_gameMapVec[row][col - i] == m_gameMapVec[row][col - i + 3] &&
			m_gameMapVec[row][col - i] == m_gameMapVec[row][col - i + 4])
			return true;
	}

	// 竖直方向(上下延伸4个)
	for (int i = 0; i < 5; i++)
	{
		if (row - i > 0 &&
			row - i + 4 < kBoardSizeNum &&
			m_gameMapVec[row - i][col] == m_gameMapVec[row - i + 1][col] &&
			m_gameMapVec[row - i][col] == m_gameMapVec[row - i + 2][col] &&
			m_gameMapVec[row - i][col] == m_gameMapVec[row - i + 3][col] &&
			m_gameMapVec[row - i][col] == m_gameMapVec[row - i + 4][col])
			return true;
	}

	// 左斜方向
	for (int i = 0; i < 5; i++)
	{
		if (row + i < kBoardSizeNum &&
			row + i - 4 > 0 &&
			col - i > 0 &&
			col - i + 4 < kBoardSizeNum &&
			m_gameMapVec[row + i][col - i] == m_gameMapVec[row + i - 1][col - i + 1] &&
			m_gameMapVec[row + i][col - i] == m_gameMapVec[row + i - 2][col - i + 2] &&
			m_gameMapVec[row + i][col - i] == m_gameMapVec[row + i - 3][col - i + 3] &&
			m_gameMapVec[row + i][col - i] == m_gameMapVec[row + i - 4][col - i + 4])
			return true;
	}

	// 右斜方向
	for (int i = 0; i < 5; i++)
	{
		if (row - i > 0 &&
			row - i + 4 < kBoardSizeNum &&
			col - i > 0 &&
			col - i + 4 < kBoardSizeNum &&
			m_gameMapVec[row - i][col - i] == m_gameMapVec[row - i + 1][col - i + 1] &&
			m_gameMapVec[row - i][col - i] == m_gameMapVec[row - i + 2][col - i + 2] &&
			m_gameMapVec[row - i][col - i] == m_gameMapVec[row - i + 3][col - i + 3] &&
			m_gameMapVec[row - i][col - i] == m_gameMapVec[row - i + 4][col - i + 4])
			return true;
	}
	return false;
}

void GameRoom::clearGame()
{
	STRU_GAME_CLEAR game_clear;
	m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&game_clear, sizeof(game_clear));
	m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&game_clear, sizeof(game_clear));
	for (int i=0; i<m_gameMapVec.size(); i++) {
		for (int j=0; j<m_gameMapVec[i].size(); j++) {
			m_gameMapVec[i][j] = 0;
		}
	}
	
	
}

void GameRoom::setRemainTime()
{
	//cout << "GameRoom::setRemainTime()" << endl;
	if (m_isStart) {
		if (curSide == 0) {
			user1RemainTime--;
			if (user1RemainTime % 10 == 0) {
				STRU_SET_REMAIN_TIME setRemainTime;
				setRemainTime.side = curSide;
				setRemainTime.remainTime = user1RemainTime;
				m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&setRemainTime, sizeof(setRemainTime));
				m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&setRemainTime, sizeof(setRemainTime));
			}
		}
		else {
			user2RemainTime--;
			if (user2RemainTime % 10 == 0) {
				STRU_SET_REMAIN_TIME setRemainTime;
				setRemainTime.side = curSide;
				setRemainTime.remainTime = user2RemainTime;
				m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId1), (char*)&setRemainTime, sizeof(setRemainTime));
				m_pLogic->m_pKernel->SendData(m_pLogic->getSockUseUserId(m_userId2), (char*)&setRemainTime, sizeof(setRemainTime));
			}
		}
	}
}
