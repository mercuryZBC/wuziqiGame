﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Kernel/Kernel.h"
#include"gamedialog.h"
#include"gamelobbydialog.h"
#include"logindialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString userId,QWidget *parent = 0);
    ~MainWindow();
    GameDialog* m_pGameDialog =nullptr;
    Kernel* m_pKernel = nullptr;
    QString m_userId;
    GameLobbyDialog* m_pGameLobby = nullptr;
    bool isOnlineRq;//客户端是否开启过网络游戏
private slots:

    void on_pb_online_clicked();

    void on_pb_pvp_clicked();

    void on_pb_pve_clicked();


public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
