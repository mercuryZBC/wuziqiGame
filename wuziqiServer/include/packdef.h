#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include "err_str.h"
#include <malloc.h>

#include<iostream>
#include<map>
#include<list>


//边界值
#define _DEF_SIZE           45
#define _DEF_BUFFERSIZE     1000
#define _DEF_PORT           8000
#define _DEF_SERVERIP       "0.0.0.0"
#define _DEF_LISTEN         128
#define _DEF_EPOLLSIZE      4096
#define _DEF_IPSIZE         16
#define _DEF_COUNT          10
#define _DEF_TIMEOUT        10
#define _DEF_SQLIEN         400
#define TRUE                true
#define FALSE               false



/*-------------数据库信息-----------------*/
#define _DEF_DB_NAME    "im"
#define _DEF_DB_IP      "0.0.0.0"
#define _DEF_DB_USER    "root"
#define _DEF_DB_PWD     "123456"
/*--------------------------------------*/
#define _MAX_PATH           (260)
#define _DEF_BUFFER         (4096)
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE           (40)
/*--------------------------------------*/

#define _DEF_CONTENT_MAX (4096)
#define FILE_BUFFER_SIZE (1024*100)
#define VIDEO_CHAT_SIZE 131072
#define USER_ID_LEN (12)
#define USER_NAME_LEN (21)
#define USER_FEELING_LEN (200)


#pragma once
#include<string.h>
#define _DEF_UDP_PORT (12345)
#define _DEF_MAX_SIZE (100)
#define _DEF_CONTENT_MAX (4096)
#define FILE_BUFFER_SIZE (1024*100)
#define VIDEO_CHAT_SIZE 131072
#define USER_ID_LEN (12)
#define USER_NAME_LEN (21)
#define USER_FEELING_LEN (200)

#define GAME_COVER_SAVE_PATH "C:/Users/Mercury/Documents/GameCover/"
#define GAME_PACK_SAVE_PATH "C:/Users/Mercury/Documents/GamePacket/"
typedef int MSG_TYPE;
//协议头
#define _DEF_UDP_PROTO_BASE (1000)

//服务端ip
#define _DEF_SERVER_IP "192.168.0.103"

#define _DEF_PACK_BASE	(2000)
#define _DEF_PACK_COUNT (10000)
typedef int PackType;
typedef int MSG_TYPE;








#define _DEF_FILE_TRANS_DATA_SIZE 4096
#define _DEF_PHONE_NUM_LEN (11)
#define _DEF_TCP_PORT (12345)

#define _DEF_TCP_PROTO_BASE (2000)
#define _DEF_TCP_PROTO_LOGIN_RQ (_DEF_TCP_PROTO_BASE+1)//登录请求
#define _DEF_TCP_PROTO_LOGIN_RQ_USEPASSWD (_DEF_TCP_PROTO_BASE+20)//登录请求使用密码
#define _DEF_TCP_PROTO_LOGIN_RS (_DEF_TCP_PROTO_BASE+2)//登录返回

#define _DEF_TCP_PROTO_FRIENDINFO_RQ (_DEF_TCP_PROTO_BASE+3)//好友信息拉取

#define _DEF_TCP_PROTO_FRIENDINFO_RS (_DEF_TCP_PROTO_BASE+4)//好友信息返回

#define _DEF_TCP_FRIEND_ONLINE (_DEF_TCP_PROTO_BASE+5)//好友上线

#define _DEF_TCP_PROTO_CHAT_RQ (_DEF_TCP_PROTO_BASE+6)//聊天请求

#define _DEF_TCP_PROTO_REGISTER_RQ (_DEF_TCP_PROTO_BASE+7)//注册请求
#define _DEF_TCP_PROTO_REGISTER_RS (_DEF_TCP_PROTO_BASE+8)//注册回复

#define _DEF_TCP_PROTO_ADDFRIEND_RQ (_DEF_TCP_PROTO_BASE+9)//加好友请求
#define _DEF_TCP_PROTO_ADDFRIEND_RS (_DEF_TCP_PROTO_BASE+10)//加好友回复


#define _DEF_TCP_PROTO_ONLINE_NOTICE (_DEF_TCP_PROTO_BASE + 18)

#define _DEF_TCP_PROTO_OFFLINE_NOTICE (_DEF_TCP_PROTO_BASE + 19)

#define _DEF_TCP_PROTO_KEEP_ALIVE (_DEF_TCP_PROTO_BASE+49)//心跳包
#define _DEF_TCP_PROTO_OFFLINE_RQ (_DEF_TCP_PROTO_BASE+50)//下线

#define _DEF_TCP_PROTO_QPS_TEST_RQ (_DEF_TCP_PROTO_BASE+55)


struct STRU_LOGIN_RQ {//登录请求
    STRU_LOGIN_RQ() :type(_DEF_TCP_PROTO_LOGIN_RQ) {}
    MSG_TYPE type;
    char userId[12];
};

struct STRU_LOGIN_RQ_USEPASSWD {//登录请求
    STRU_LOGIN_RQ_USEPASSWD() :type(_DEF_TCP_PROTO_LOGIN_RQ_USEPASSWD) {}
    MSG_TYPE type;
    char userId[12];
    char passwd[21];
};

enum LoginState {
    userIdOrpasswdError = 0,
    LoginSuccess = 1,
    userIsOnline = 2
};

struct STRU_LOGIN_RS {//登录返回
    STRU_LOGIN_RS() :type(_DEF_TCP_PROTO_LOGIN_RS) {}
    MSG_TYPE type;
    LoginState state;
    int iconId;
    char userName[21];
    char feeling[200];
};

enum FriendState {//好友在线情况
    offline = 0,
    online = 1
};


struct STRU_FRIENDINFO_RQ {//拉取好友信息
    STRU_FRIENDINFO_RQ() :type(_DEF_TCP_PROTO_FRIENDINFO_RQ) {}
    MSG_TYPE type;
};


struct STRU_FRIENDINFO_RS {//返回好友信息
    STRU_FRIENDINFO_RS() :type(_DEF_TCP_PROTO_FRIENDINFO_RS) {}
    MSG_TYPE type;
    FriendState state;
    char userId[12];
    char userName[21];
    int iconId;
    char feeling[200];
};

struct STRU_FRIEND_ONLINE {//好友上线通知
    STRU_FRIEND_ONLINE() :type(_DEF_TCP_FRIEND_ONLINE) {}
    MSG_TYPE type;
    char friendId[12];
};

struct STRU_OFFLINE_RQ {//下线
    STRU_OFFLINE_RQ() :type(_DEF_TCP_PROTO_OFFLINE_RQ) {}
    MSG_TYPE type;
};

struct STRU_CHAT_RQ {
    STRU_CHAT_RQ() :type(_DEF_TCP_PROTO_CHAT_RQ) {}
    MSG_TYPE type;
    char userId[12];
    char friendId[12];
    char time[100];
    char chatDate[1024];

};

enum RegisterState {
    registerSuccess = 0,
    userIsExist = 1,
    serverException = 2
};
struct STRU_REGISTER_RQ {
    STRU_REGISTER_RQ() :type(_DEF_TCP_PROTO_REGISTER_RQ) {}
    MSG_TYPE type;
    char RegisterId[12];
    char RegisterName[21];
    char RegisterPasswd[21];
};

struct STRU_REGISTER_RS {
    STRU_REGISTER_RS() :type(_DEF_TCP_PROTO_REGISTER_RS) {}
    MSG_TYPE type;
    int registerState;
};

struct STRU_ADD_FRIEND_RQ {
    STRU_ADD_FRIEND_RQ() :type(_DEF_TCP_PROTO_ADDFRIEND_RQ) {}
    MSG_TYPE type;
    char friendId[12];
};

enum addFriendState {
    addSuccess = 0,
    noThisUser = 1,
    userIsFriend = 2,
    addFriendServerException = 3
};

struct STRU_ADD_FRIEND_RS {
    STRU_ADD_FRIEND_RS() :type(_DEF_TCP_PROTO_ADDFRIEND_RS) {}
    MSG_TYPE type;
    int addFriendState;
};
struct STRU_ONLINE_NOTICE {
    STRU_ONLINE_NOTICE() :type(_DEF_TCP_PROTO_ONLINE_NOTICE) {}
    MSG_TYPE type;
    char userId[12];
};

struct STRU_OFFLINE_NOTICE {
    STRU_OFFLINE_NOTICE() :type(_DEF_TCP_PROTO_OFFLINE_NOTICE) {}
    MSG_TYPE type;
    char userId[12];
};

struct STRU_QPS_TEST{
    STRU_QPS_TEST():type(_DEF_TCP_PROTO_QPS_TEST_RQ){}
    MSG_TYPE type;
    char userId[12];
};

/*--------------------------游戏相关------------------------------------*/

#define _DEF_TCP_PROTO_CREATE_ROOM_RQ (_DEF_TCP_PROTO_BASE+100)//创建新房间请求
#define _DEF_TCP_PROTO_CREATE_ROOM_RS (_DEF_TCP_PROTO_BASE+101)//创建新房间回复
#define _DEF_TCP_PROTO_LOAD_EXIST_ROOM_RQ (_DEF_TCP_PROTO_BASE+102)//获取已经存在的房间
#define _DEF_TCP_PROTO_LOAD_EXIST_ROOM_RS (_DEF_TCP_PROTO_BASE+103)
#define _DEF_TCP_PROTO_ROOM_CLOSE (_DEF_TCP_PROTO_BASE+104)
#define _DEF_TCP_PROTO_PLAYER_EXIT_ROOM (_DEF_TCP_PROTO_BASE+105)
#define _DEF_TCP_PROTO_JOIN_ROOM (_DEF_TCP_PROTO_BASE+106)
#define _DEF_TCP_PROTO_JOIN_ROOM_RS (_DEF_TCP_PROTO_BASE+107)
#define _DEF_TCP_PROTO_GAME_READY (_DEF_TCP_PROTO_BASE + 108)
#define _DEF_TCP_PROTO_GAME_START (_DEF_TCP_PROTO_BASE + 109)
#define _DEF_TCP_PROTO_SET_REMAIN_TIME (_DEF_TCP_PROTO_BASE + 110)
#define _DEF_TCP_PROTO_PLAYER_CHESS (_DEF_TCP_PROTO_BASE + 111)
#define _DEF_TCP_PROTO_GAME_OVER (_DEF_TCP_PROTO_BASE + 112)
#define _DEF_TCP_PROTO_GAME_CLEAR (_DEF_TCP_PROTO_BASE + 113)//清空棋盘


struct STRU_LOAD_EXIST_ROOM_RQ {
    STRU_LOAD_EXIST_ROOM_RQ() :type(_DEF_TCP_PROTO_LOAD_EXIST_ROOM_RQ) {}
    MSG_TYPE type;
};

struct STRU_LOAD_EXIST_ROOM_RS {
    STRU_LOAD_EXIST_ROOM_RS() :type(_DEF_TCP_PROTO_LOAD_EXIST_ROOM_RS) {}
    MSG_TYPE type;
    int roomId;//房间号
    bool isLock;//是否为私密房间
    int PlayerNum;//玩家数
    bool user1Exist;
    bool user2Exist;
    char user1Id[12];
    char user2Id[12];
    int user1IconId;
    int user2IconId;
};


struct STRU_CREATE_ROOM_RQ {
    STRU_CREATE_ROOM_RQ() :type(_DEF_TCP_PROTO_CREATE_ROOM_RQ) {}
    MSG_TYPE type;
    char userId[12];
};

struct STRU_CREATE_ROOM_RS {
    STRU_CREATE_ROOM_RS() :type(_DEF_TCP_PROTO_CREATE_ROOM_RS) {}
    MSG_TYPE type;
    STRU_LOAD_EXIST_ROOM_RS roompack;

};

struct STRU_ROOM_CLOSE {
    STRU_ROOM_CLOSE() :type(_DEF_TCP_PROTO_ROOM_CLOSE) {}
    MSG_TYPE type;
    int roomId;
};

struct STRU_PLAYER_EXIT_ROOM {
    STRU_PLAYER_EXIT_ROOM() :type(_DEF_TCP_PROTO_PLAYER_EXIT_ROOM) {}
    MSG_TYPE type;
    int roomId;
};

struct STRU_JOIN_ROOM {
    STRU_JOIN_ROOM() :type(_DEF_TCP_PROTO_JOIN_ROOM) {}
    MSG_TYPE type;
    int roomId;
};

enum joinRoomState {
    joinSuccess = 0,
    playerExist = 1,
    joinError = 2,
    roomIsNotExist = 3
};

struct STRU_JOIN_ROOM_RS {
    STRU_JOIN_ROOM_RS() :type(_DEF_TCP_PROTO_JOIN_ROOM_RS) {}
    MSG_TYPE type;
    int state;
    STRU_LOAD_EXIST_ROOM_RS roompack;
};

struct STRU_GAME_READY {
    STRU_GAME_READY() :type(_DEF_TCP_PROTO_GAME_READY) {}
    MSG_TYPE type;
    int roomId;
};

struct STRU_GAME_STRAT {
    STRU_GAME_STRAT() :type(_DEF_TCP_PROTO_GAME_START) {}
    MSG_TYPE type;
    char user1name[12];
    char user2name[12];
    bool user1isBlack;
    int remainTime;
};


struct STRU_SET_REMAIN_TIME {
    STRU_SET_REMAIN_TIME() :type(_DEF_TCP_PROTO_SET_REMAIN_TIME) {}
    MSG_TYPE type;
    bool side;
    int roomId;
    int remainTime;
};

struct STRU_PLAYER_CHESS {
    STRU_PLAYER_CHESS() :type(_DEF_TCP_PROTO_PLAYER_CHESS) {}
    MSG_TYPE type;
    bool side;
    int roomId;
    int chessRow;
    int chessCol;
};

struct STRU_GAME_OVER {
    STRU_GAME_OVER():type(_DEF_TCP_PROTO_GAME_OVER) {}
    MSG_TYPE type;
    int roomId;
    bool winSide;//黑色方或白色方
};

struct STRU_GAME_CLEAR {
    STRU_GAME_CLEAR() :type(_DEF_TCP_PROTO_GAME_CLEAR) {}
    MSG_TYPE type;
    int roomId;
};


struct STRU_KEEP_ALIVE{
    STRU_KEEP_ALIVE():type(_DEF_TCP_PROTO_KEEP_ALIVE){}
    MSG_TYPE type;
};
