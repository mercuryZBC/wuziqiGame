#include "gamelobbydialog.h"
#include "ui_gamelobbydialog.h"
#include<QDebug>
#include<QMessageBox>
#include"Config/config.h"
#include"./friendWidgetItem/friendwidgetitem.h"
GameLobbyDialog::GameLobbyDialog(QString userId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameLobbyDialog)
{
    ui->setupUi(this);
    m_userId = userId;
    m_pKernel = Kernel::getInstance();
    m_vbLayout = new QVBoxLayout;
    m_vbLayout->setContentsMargins(0,0,0,0);
    m_vbLayout->setSpacing(3);
    m_pGameDialog = new GameDialog();
    ui->wdg_friendList->setLayout(m_vbLayout);
    //每个控件的间距
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(3);
    m_gridLayout->setContentsMargins(0,0,0,0);
    ui->wdg_roomList->setLayout(m_gridLayout);
    qRegisterMetaType<STRU_CREATE_ROOM_RS>("STRU_CREATE_ROOM_RS");
    connect(m_pKernel,&Kernel::SIG_createRoomRs,this,&GameLobbyDialog::createRoomRsComing);
    connect(m_pKernel,&Kernel::SIG_loadExistRoomRs,this,&GameLobbyDialog::loadExistRoomRsComing);
    connect(m_pKernel,&Kernel::SIG_roomIsBeClosed,this,&GameLobbyDialog::roomBeCloseComing);
    connect(m_pGameDialog,&GameDialog::SIG_exitOnlineGameDialog,this,&GameLobbyDialog::playerGameExitRoomComing);
    qRegisterMetaType<STRU_JOIN_ROOM_RS>("STRU_JOIN_ROOM_RS");
    connect(m_pKernel,&Kernel::SIG_joinRoomRs,this,&GameLobbyDialog::joinRoomRSComing);
    connect(m_pGameDialog,&GameDialog::SIG_readyGame,this,&GameLobbyDialog::readyGameComing);
    qRegisterMetaType<STRU_GAME_STRAT>("STRU_GAME_STRAT");
    connect(m_pKernel,&Kernel::SIG_gameStart,m_pGameDialog,&GameDialog::onlineGameStart);
    qRegisterMetaType<STRU_SET_REMAIN_TIME>("STRU_SET_REMAIN_TIME");
    connect(m_pKernel,&Kernel::SIG_setRemainTime,m_pGameDialog,&GameDialog::setOnlineRemainTime);
    qRegisterMetaType<STRU_PLAYER_CHESS>("STRU_PLAYER_CHESS");
    connect(m_pKernel,&Kernel::SIG_opponentChess,m_pGameDialog,&GameDialog::opponentChessComing);
    connect(m_pKernel,&Kernel::SIG_gameOver,m_pGameDialog,&GameDialog::gameOverComing);

    connect(m_pGameDialog,&GameDialog::SIG_playerChess,m_pKernel,&Kernel::dealPlayChess);
    connect(m_pGameDialog,&GameDialog::SIG_gameDialogClose,this,&GameLobbyDialog::show);
    //connect(m_pKernel,&Kernel::SIG_gameClear,m_pGameDialog,);
}

GameLobbyDialog::~GameLobbyDialog()
{
    delete ui;
}

void GameLobbyDialog::LoginRsComing(int state, int iconId, QString userName, QString feeling)
{
    qDebug()<<"GameLobbyDialog::LoginRsComing";
    if(state == userIsOnline){
        QMessageBox::warning(nullptr,"warning","用户已经登录，请勿重复登录");
    }
    else{//登录成功
        m_iconId=iconId;
        m_userName=userName;
        ui->lable_name->setText(userName);//设置显示用户名
        ui->le_feeling->setText(feeling);//设置个签

        //获取好友列表
        m_pKernel->getFriendList();
//        //获取群聊列表
//        m_pKernel->getGroupList();
        QString iconPath=QString(":/res/tx/%1.png").arg(m_iconId);
        ui->pb_icon->setIcon(QIcon(iconPath));
        repaint();
        show();
    }
}

void GameLobbyDialog::FriendInfoComing(int state, QString id, QString name, int iconId, QString feeling)
{
    qDebug()<<__func__;
    CLIENT_FRIEND_INFO struFriendInfo;
    memset(&struFriendInfo,0,sizeof(struFriendInfo));
    strncpy(struFriendInfo.myOwnId,this->m_userId.toStdString().c_str(),this->m_userId.length());
    strncpy(struFriendInfo.id,id.toStdString().c_str(),sizeof(struFriendInfo.id));
    strncpy(struFriendInfo.name,name.toStdString().c_str(),sizeof(struFriendInfo.name));
    strncpy(struFriendInfo.feeling,feeling.toStdString().c_str(),sizeof(struFriendInfo.feeling));
    struFriendInfo.iconId = iconId;
    struFriendInfo.state = state;
    m_mapFriendIdToInfo[id] = struFriendInfo;//将好友信息结构体
    friendWidgetItem* item=new friendWidgetItem(struFriendInfo,this);
    //绑定消息发送信号槽
//    connect(item,&friendWidgetItem::SIG_itemSendChatMeg,this,&MainWindow::onChatDataSend);
//    connect(item,&friendWidgetItem::SIG_itemSendFileRequest,m_pKernel,&Kernel::dealSendFileRequest);
//    connect(item,&friendWidgetItem::SIG_itemRecvFileRequest,FileTransFerDialog::getInstance(),&FileTransFerDialog::dealRecvFileRequest);
    m_listFriendItem.push_back({id,item});//将好友id,和对应的friend加入链表
    if(!m_mapIdToFriendItem.count(id)){
        m_mapIdToFriendItem[id] = item;
    }
    m_vbLayout->addWidget(item);
    //m_pGameLobby->FriendListAdd(item);
    repaint();
}

void GameLobbyDialog::onFriendOnline(QString friendId)
{
    qDebug()<<"GameLobbyDialog::onFriendOnline";
    for(auto ite:m_listFriendItem){//在好友链表中查找好友对应的item
        if(ite.first==friendId){
            ite.second->setOnline();
        }
    }
}

void GameLobbyDialog::createRoomRsComing(STRU_CREATE_ROOM_RS createRoomRs)
{
    qDebug()<<"GameLobbyDialog::createRoomRsComing";
    m_pGameDialog->initOnlineGame(m_userId,createRoomRs.roompack);
}

void GameLobbyDialog::loadExistRoomRsComing(STRU_LOAD_EXIST_ROOM_RS loadExistRoomRs)
{
    qDebug()<<"GameLobbyDialog::loadExistRoomRsComing";
    if(!m_mapRoomIdToRoomItem.count(loadExistRoomRs.roomId)){
        GameRoomWidgetItem* roomWidget = new GameRoomWidgetItem(loadExistRoomRs);
        connect(roomWidget,&GameRoomWidgetItem::SIG_joinGameRoom,this,&GameLobbyDialog::joinRoomComing);
        m_mapRoomIdToRoomItem[loadExistRoomRs.roomId] = roomWidget;
        m_gridLayout->addWidget(roomWidget);
    }
    else{
        m_mapRoomIdToRoomItem[loadExistRoomRs.roomId]->updateRoomState(loadExistRoomRs);
    }
    if(m_pGameDialog->m_isOnlineGame && m_pGameDialog->m_roomId == loadExistRoomRs.roomId){
        m_pGameDialog->updateOnlineGame(loadExistRoomRs);
    }
}

void GameLobbyDialog::roomBeCloseComing(int roomId)
{
    qDebug()<<"GameLobbyDialog::roomBeCloseComing";
    if(m_mapRoomIdToRoomItem.count(roomId)){
        delete m_mapRoomIdToRoomItem[roomId];
        m_mapRoomIdToRoomItem.erase(m_mapRoomIdToRoomItem.find(roomId));
    }
}

void GameLobbyDialog::playerGameExitRoomComing(int roomId)
{
    qDebug()<<"GameLobbyDialog::playerGameRoomComing";
    STRU_PLAYER_EXIT_ROOM playerExitRoomPack;
    playerExitRoomPack.roomId = roomId;
    m_pKernel->m_pMedia->SendData(NULL,(char*)&playerExitRoomPack,sizeof(STRU_PLAYER_EXIT_ROOM));
}

void GameLobbyDialog::joinRoomComing(int roomId)
{
    if(m_pGameDialog != nullptr && m_pGameDialog->m_isOnlineGame == true){
        QMessageBox::information(this,"游戏提醒","你当前已经在房间里");
    }
    else{
        STRU_JOIN_ROOM joinRoomRq;
        joinRoomRq.roomId = roomId;
        m_pKernel->m_pMedia->SendData(NULL,(char*)&joinRoomRq,sizeof(joinRoomRq));
    }
}
//enum joinRoomState{
//    joinSuccess = 0,
//    playerExist = 1,
//    joinError = 2,
//    roomIsNotExist = 3
//};
void GameLobbyDialog::joinRoomRSComing(STRU_JOIN_ROOM_RS joinRoomRs)
{
    qDebug()<<"GameLobbyDialog::joinRoomRSComing";
    if(joinRoomRs.state == joinSuccess){
        m_pGameDialog->initOnlineGame(m_userId,joinRoomRs.roompack);
    }
    else if(joinRoomRs.state == playerExist){
        QMessageBox::information(this,"游戏提醒","该座位已存在玩家");
    }
    else if(joinRoomRs.state == joinError){
        QMessageBox::information(this,"游戏提醒","加入失败");
    }
    else if(joinRoomRs.state == roomIsNotExist){
        QMessageBox::information(this,"游戏提醒","房间已被销毁");
    }

}

void GameLobbyDialog::readyGameComing(int roomId)
{
    qDebug()<<"GameLobbyDialog::readyGameComing";
    STRU_GAME_READY gameReadyPack;
    gameReadyPack.roomId = roomId;
    m_pKernel->m_pMedia->SendData(NULL,(char*)&gameReadyPack,sizeof(gameReadyPack));
}



void GameLobbyDialog::on_pb_newMatch_clicked()
{

}


void GameLobbyDialog::on_pb_quickStart_clicked()
{

}


void GameLobbyDialog::on_pb_newRoom_clicked()
{
    qDebug()<<"GameLobbyDialog::on_pb_newRoom_clicked";
    m_pKernel->createRoom(m_userId);
    this->hide();
}

void GameLobbyDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit SIG_showMainWindow();
}

