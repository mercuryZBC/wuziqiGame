#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamedialog.h"
#include "chessboardwidget.h"
#include"gamelobbydialog.h"
MainWindow::MainWindow(QString userId, QWidget *parent): QMainWindow(parent)
{
    ui->setupUi(this);
    m_userId = userId;
    isOnlineRq = false;
    m_pGameDialog = nullptr;
    setWindowTitle("五子棋");
    //加载已经存在的房间
}

MainWindow::~MainWindow()
{
    if(m_pGameLobby){
        delete m_pGameLobby;
    }
    if(m_pGameDialog){
        delete m_pGameDialog;
    }
    delete ui;
}


//void MainWindow::on_pb_offline_clicked()
//{
//    m_pGameDialog->show();
//}


void MainWindow::on_pb_online_clicked()
{
    if(isOnlineRq == false){
        if(m_userId!=""){
            m_pGameLobby = new GameLobbyDialog(m_userId);
        }else{
            m_pGameLobby = new GameLobbyDialog();
        }
        m_pGameDialog = nullptr;
        m_pKernel = Kernel::getInstance();
        this->hide();
        connect(m_pKernel,&Kernel::SIG_loginResult,m_pGameLobby,&GameLobbyDialog::LoginRsComing);
        connect(m_pKernel,&Kernel::SIG_FriendInfoComing,m_pGameLobby,&GameLobbyDialog::FriendInfoComing);
        connect(m_pKernel,&Kernel::SIG_FriendOnline,m_pGameLobby,&GameLobbyDialog::onFriendOnline);
        qRegisterMetaType<STRU_LOAD_EXIST_ROOM_RS>("STRU_LOAD_EXIST_ROOM_RS");
        connect(m_pKernel,&Kernel::SIG_loadExistRoomRs,m_pGameLobby,&GameLobbyDialog::loadExistRoomRsComing);
        connect(m_pKernel,&Kernel::SIG_roomIsBeClosed,m_pGameLobby,&GameLobbyDialog::roomBeCloseComing);
        connect(m_pGameLobby,&GameLobbyDialog::SIG_showMainWindow,this,&MainWindow::show);
//        m_pKernel->sendLoginRq(m_userId);
//        m_pKernel->loadExistRoomRq();
//        isOnlineRq = true;
//        m_pGameLobby->show();
//        this->hide();
    }
}


void MainWindow::on_pb_pvp_clicked()
{
    if(m_pGameDialog){
        delete m_pGameDialog;
    }
    m_pGameDialog = new GameDialog(pvpGame);
    m_pGameDialog->show();
    this->hide();
}


void MainWindow::on_pb_pve_clicked()
{
    if(m_pGameDialog){
        delete m_pGameDialog;
    }
    m_pGameDialog = new GameDialog(pveGame);
    m_pGameDialog->show();
    this->hide();
}

