#include<QDebug>
#include<QMessageBox>
#include<QTextCodec>
#include<string>
#include <QMetaType>
#include<QFileDialog>
#include<errno.h>
#include<string.h>
#include<winsock2.h>
#include<string.h>
#include"Kernel.h"
#include"Config/ClientConfig.h"
Kernel* Kernel::m_pKernel=nullptr;
QString Kernel::gb2312ToUtf8(char *gb2312)
{
    //    //new一个转码对象
    //    QTextCodec* gb2312code=QTextCodec::codecForName("gb2312");
    //    //从gb2312转到utf8，返回值是QString
    //    return gb2312code->toUnicode(gb2312);
    return gb2312;
}

void Kernel::utf8ToGb2312(QString utf8, char *gb2312, int gb2312Len)
{
    //    memset(gb2312,0,gb2312Len);
    //    //new一个转码对象
    //    QTextCodec* gb2312code=QTextCodec::codecForName("gb2312");
    //    //从utf8转到gb2312
    //    QByteArray ba=gb2312code->fromUnicode(utf8);
    //    //往目标空间中拷贝转码后的数据
    //    strcpy_s(gb2312,gb2312Len,ba.data());
    strcpy_s(gb2312,gb2312Len,utf8.toStdString().c_str());
}

Kernel::Kernel()
{
    m_pMedia=new TcpClientNetMediator;
    if(m_pMedia->OpenNet()){//打开网络失败
        QMessageBox::warning(nullptr,"warning","Tcp open net fail");
        exit(0);
    }
    bindTypeAndFun();
}

Kernel::~Kernel()
{
    qDebug()<<"Kernel::~Kernel";
    STRU_OFFLINE_RQ offlineRq;
    m_pMedia->SendData(NULL,(char*)&offlineRq,sizeof(offlineRq));//发送下线请求
    if(m_pMedia){
        delete m_pMedia;
        m_pMedia=nullptr;
    }
}
Kernel* Kernel::getInstance()
{
    qDebug()<<"Kernel::getInstance";
    if (nullptr == m_pKernel) {
        m_pKernel = new Kernel;
    }
    return m_pKernel;
}

void Kernel::destoryInstance(Kernel*& pKernel) {//回收内存空间
    if (m_pKernel) {
        delete m_pKernel;
        m_pKernel = nullptr;
     }
    pKernel = nullptr;
}

void Kernel::sendLoginRq(QString userId)
{
    qDebug()<<"Kernel::sendLoginRq";
    STRU_LOGIN_RQ loginRq;
    memset(loginRq.userId,0,sizeof(loginRq.userId));
    strncpy(loginRq.userId,userId.toStdString().c_str(),userId.length());
    m_pMedia->SendData(NULL,(char*)&loginRq,sizeof(loginRq));

}

void Kernel::getFriendList()
{
    qDebug()<<"Kernel::getFriendList";
    STRU_FRIENDINFO_RQ friendInfoRq;
    m_pMedia->SendData(NULL,(char*)&friendInfoRq,sizeof(friendInfoRq));
}

void Kernel::bindTypeAndFun()
{
    m_mapTypeToFun[_DEF_TCP_PROTO_LOGIN_RS] = &Kernel::dealLoginResult;
    m_mapTypeToFun[_DEF_TCP_PROTO_FRIENDINFO_RS] = &Kernel::dealFriendInfoResult;
    m_mapTypeToFun[_DEF_TCP_FRIEND_ONLINE]=&Kernel::dealFriendOnline;
    m_mapTypeToFun[_DEF_TCP_PROTO_CREATE_ROOM_RS] = &Kernel::dealCreateRoomRs;
    m_mapTypeToFun[_DEF_TCP_PROTO_LOAD_EXIST_ROOM_RS] =&Kernel::dealLoadExistRoomRs;
    m_mapTypeToFun[_DEF_TCP_PROTO_ROOM_CLOSE] = &Kernel::dealRoomIsBeClosed;
    m_mapTypeToFun[_DEF_TCP_PROTO_JOIN_ROOM_RS] = &Kernel::dealJoinRoomRs;
    m_mapTypeToFun[_DEF_TCP_PROTO_GAME_START] = &Kernel::dealStartGame;
    m_mapTypeToFun[_DEF_TCP_PROTO_SET_REMAIN_TIME] = &Kernel::dealsetTime;
    m_mapTypeToFun[_DEF_TCP_PROTO_PLAYER_CHESS] = &Kernel::dealOpponentChess;
    m_mapTypeToFun[_DEF_TCP_PROTO_GAME_OVER] = &Kernel::dealGameOver;
    m_mapTypeToFun[_DEF_TCP_PROTO_GAME_CLEAR] = &Kernel::dealGameClear;
}

void Kernel::dealReadyData(long lSendip, char *buf, int nLen){
    Q_UNUSED(nLen)
    qDebug()<< " Kernel::dealReadyData";
    MSG_TYPE type = *(int*)buf;

    if (m_mapTypeToFun.count(type)) {
        (this->*m_mapTypeToFun[type])(buf);
    }
    else {
        qDebug()<< "Kernel::dealReadyData:not have function to match the protocol head";
    }
}

void Kernel::dealLoginResult(char *buf){
    qDebug()<<"Kernel::dealLoginResult";
    //拆包
    STRU_LOGIN_RS loginRs;
    loginRs=*(STRU_LOGIN_RS*)buf;
    QString userName=gb2312ToUtf8(loginRs.userName);
    QString feeling=gb2312ToUtf8(loginRs.feeling);
    emit SIG_loginResult(loginRs.state,loginRs.iconId,
                         userName,feeling);//向mainwindow发送登录请求返回信号信号
}

void Kernel::dealFriendInfoResult(char *buf)
{
    qDebug()<<"Kernel::dealFriendInfoResult";
    STRU_FRIENDINFO_RS friendInfoRs=*(STRU_FRIENDINFO_RS*)buf;

    //字符转编码
    QString userId=gb2312ToUtf8(friendInfoRs.userId);
    QString userName=gb2312ToUtf8(friendInfoRs.userName);
    QString feeling=gb2312ToUtf8(friendInfoRs.feeling);
    //向mainwindow发送好友信息到来信号
    emit SIG_FriendInfoComing(friendInfoRs.state,userId,userName,friendInfoRs.iconId,feeling);
}

void Kernel::dealFriendOnline(char *buf)
{
    qDebug()<<"Kernel::dealFriendOnline";
    STRU_FRIEND_ONLINE friendOnlineInfo=*(STRU_FRIEND_ONLINE*)buf;
    QString friendId=gb2312ToUtf8(friendOnlineInfo.friendId);
    emit SIG_FriendOnline(friendId);
    return;
}

void Kernel::dealRoomIsBeClosed(char *buf)
{
    qDebug()<<"Kernel::dealRoomIsClosed";
    STRU_ROOM_CLOSE roomClosePack = *(STRU_ROOM_CLOSE*)buf;
    emit SIG_roomIsBeClosed(roomClosePack.roomId);
}

void Kernel::createRoom(QString userId)
{
    qDebug()<<"Kernel::createRoom";
    STRU_CREATE_ROOM_RQ createRoomRq;
    strncpy(createRoomRq.userId,userId.toStdString().c_str(),userId.length());
    m_pMedia->SendData(NULL,(char*)&createRoomRq,sizeof(createRoomRq));
}

void Kernel::loadExistRoomRq()
{
    STRU_LOAD_EXIST_ROOM_RQ loadRoomRq;
    m_pMedia->SendData(NULL,(char*)&loadRoomRq,sizeof(loadRoomRq));
}

void Kernel::dealOpponentChess(char *buf)
{
    STRU_PLAYER_CHESS playerChess = *(STRU_PLAYER_CHESS*)buf;
    emit SIG_opponentChess(playerChess);
}

void Kernel::dealGameOver(char *buf)
{
    STRU_GAME_OVER gameOverPack = *(STRU_GAME_OVER*)buf;
    emit SIG_gameOver(gameOverPack.winSide);
}

void Kernel::dealPlayChess(STRU_PLAYER_CHESS playerChess)
{
    qDebug()<<"Kernel::dealPlayChess";
    m_pMedia->SendData(NULL,(char*)&playerChess,sizeof(playerChess));
}

void Kernel::dealCreateRoomRs(char *buf)
{
    qDebug()<<"Kernel::dealCreateRoomRs";
    STRU_CREATE_ROOM_RS createRoomRs = *(STRU_CREATE_ROOM_RS*)buf;
    emit SIG_createRoomRs(createRoomRs);
}

void Kernel::dealLoadExistRoomRs(char *buf)
{

    STRU_LOAD_EXIST_ROOM_RS loadExistRoomRs = *(STRU_LOAD_EXIST_ROOM_RS*)buf;
    emit SIG_loadExistRoomRs(loadExistRoomRs);
}

void Kernel::dealJoinRoomRs(char *buf)
{
    STRU_JOIN_ROOM_RS joinRoomRs = *(STRU_JOIN_ROOM_RS*)buf;
    emit SIG_joinRoomRs(joinRoomRs);
}

void Kernel::dealStartGame(char *buf)
{
    STRU_GAME_STRAT gameStart = *(STRU_GAME_STRAT*)buf;
    emit SIG_gameStart(gameStart);
}

void Kernel::dealsetTime(char *buf)
{
    STRU_SET_REMAIN_TIME setTimePack = *(STRU_SET_REMAIN_TIME*)buf;
    emit SIG_setRemainTime(setTimePack);
}

void Kernel::dealGameClear(char *buf)
{
    emit SIG_gameClear();
}
