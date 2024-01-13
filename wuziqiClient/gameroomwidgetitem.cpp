#include "gameroomwidgetitem.h"
#include "ui_gameroomwidgetitem.h"
#include<QMessageBox>
GameRoomWidgetItem::GameRoomWidgetItem(STRU_LOAD_EXIST_ROOM_RS& pack,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameRoomWidgetItem)
{
    ui->setupUi(this);
    m_roomId = pack.roomId;
    m_user1IconId = 999;
    m_user2IconId = 999;
    if(pack.user1Exist){
        m_user1Id = pack.user1Id;
        m_user1IconId = pack.user1IconId;
    }
    else{
        m_user1Id = "";
    }
    if(pack.user2Exist){
        m_user2Id = pack.user2Id;
        m_user2IconId = pack.user2IconId;
    }
    else{
        m_user2Id = "";
    }
    setIcon();
}

GameRoomWidgetItem::~GameRoomWidgetItem()
{
    delete ui;
}

void GameRoomWidgetItem::setIcon()
{
    ui->lb_roomId->setText(QString("房间号 %1").arg(m_roomId));
    QString iconPath1=QString(":/res/tx/%1.png").arg(m_user1IconId);
    ui->pb_user1Icon->setIcon(QIcon(iconPath1));
    QString iconPath2=QString(":/res/tx/%2.png").arg(m_user2IconId);
    ui->pb_user2Icon->setIcon(QIcon(iconPath2));
}

void GameRoomWidgetItem::updateRoomState(STRU_LOAD_EXIST_ROOM_RS &pack)
{
    if(pack.user1Exist){
        m_user1Id = pack.user1Id;
        m_user1IconId = pack.user1IconId;
    }
    else{
        m_user1Id = "";
        m_user1IconId = 999;
    }
    if(pack.user2Exist){
        m_user2Id = pack.user2Id;
        m_user2IconId = pack.user2IconId;
    }
    else{
        m_user2Id = "";
        m_user2IconId = 999;
    }
    setIcon();
}

void GameRoomWidgetItem::on_pb_user1Icon_clicked()
{
    if(m_user1Id == ""){
        emit SIG_joinGameRoom(m_roomId);
    }
    else{
        QMessageBox::information(this,"游戏提醒","当前座位已存在玩家");
    }
}


void GameRoomWidgetItem::on_pb_user2Icon_clicked()
{
    if(m_user2Id == ""){
        emit SIG_joinGameRoom(m_roomId);
    }
    else{
        QMessageBox::information(this,"游戏提醒","当前座位已存在玩家");
    }
}

