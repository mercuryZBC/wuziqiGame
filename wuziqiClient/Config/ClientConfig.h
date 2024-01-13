
#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H
#include"config.h"
struct CLIENT_FRIEND_INFO{//好友信息结构体，传参用
    char myOwnId[USER_ID_LEN];
    char id[USER_ID_LEN];
    char name[USER_NAME_LEN];
    char feeling[USER_FEELING_LEN];
    int iconId;
    int state;
};
enum{
    textMsg = 0,
    fileMsg = 1
};
struct CLIENT_MESSAGE_INFO{//好友信息结构体，传参用
    char id[12];
    char name[100];
    int iconId;
    int type;
    char chatMsg[1024];//聊天内容
};

struct CLIENT_ROOM_INFO{
    int RoomId;//房间号
};



struct CLIENT_FILE_INFO{//文件信息
    int seq;
    int fileType;
    int fileSize;
    char fileName[2048];
    char fileOriginName[2048];
    char sendUserId[12];
    char recvUserId[12];
};

struct CLIENT_VIDEO_CHAT_INFO{
    char sendUserId[12];
    char recvUserId[12];
};

#endif // CLIENTCONFIG_H
