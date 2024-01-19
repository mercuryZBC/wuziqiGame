#pragma once
#include"../NetMediator/TcpClientNetMediator.h"
#include"Config/config.h"
#include<QObject>
#include<QMap>
#include"Config/ClientConfig.h"
//#include"../FileTransfer/filetransferdialog.h"
class Kernel:public QObject{
    Q_OBJECT
public:
    static Kernel* m_pKernel;

public:
    typedef void(Kernel::*P_FUN)(char*);
    QMap<MSG_TYPE, P_FUN>m_mapTypeToFun;
    QString gb2312ToUtf8(char *gb2312);
    void utf8ToGb2312(QString utf8, char *gb2312, int gb2312Len);
private:
    Kernel();
    Kernel(const Kernel&) = delete;
    ~Kernel();

public:
    INetMediator* m_pMedia;
    static Kernel* getInstance();
    static void destoryInstance(Kernel*& pKernel);
public slots:
    void sendLoginRq(QString userId);
    void sendLoginRq(QString userId,QString passwd);
    void sendRegisterRq(QString userId,QString name,QString passwd);
    void getFriendList();
public://处理TCP消息
    void bindTypeAndFun();//绑定协议头类型和对应处理函数
    void dealReadyData(long lSendip, char *buf, int nLen);
    void dealLoginResult(char *buf);
    void dealFriendInfoResult(char* buf);
    void dealFriendOnline(char* buf);
    void dealRoomIsBeClosed(char* buf);
    void dealRegisterRs(char* buf);
public:
    void dealCreateRoomRs(char *buf);
    void dealLoadExistRoomRs(char *buf);
    void dealJoinRoomRs(char* buf);
    void dealStartGame(char* buf);
    void dealsetTime(char* buf);
    void dealGameClear(char* buf);//处理init房间
    //创建房间
    void createRoom(QString userId);
    //加载已存在的房间
    void loadExistRoomRq();

    void dealOpponentChess(char* buf);//对手chess

    void dealGameOver(char* buf);
    //处理下线
    void dealOfflineRq();
signals:
    //登录信息到来信号 ->gameLobby
    void SIG_loginResult(int state,int iconId,QString userName,QString feeling);
    //好友信息到来信号 ->gameLobby
    void SIG_FriendInfoComing(int state,QString userId,QString userName,int iconId,QString feeling);
    //好友上线信号 ->gameLobby
    void SIG_FriendOnline(QString friendId);
    //创建房间回复到来信号->gameLobby
    void SIG_createRoomRs(STRU_CREATE_ROOM_RS);
    //加载已经存在的房间回复到来信号 ->gameLobby
    void SIG_loadExistRoomRs(STRU_LOAD_EXIST_ROOM_RS);
    //房间被销毁信号 ->gameLobby
    void SIG_roomIsBeClosed(int roomId);
    void SIG_joinRoomRs(STRU_JOIN_ROOM_RS joinRoomRs);
    void SIG_gameStart(STRU_GAME_STRAT);
    void SIG_setRemainTime(STRU_SET_REMAIN_TIME);

    void SIG_opponentChess(STRU_PLAYER_CHESS);
    void SIG_gameOver(bool winSide);
    void SIG_gameClear();
    void SIG_Register(int statusCode);
public slots:
    void dealPlayChess(STRU_PLAYER_CHESS playerChess);
};
