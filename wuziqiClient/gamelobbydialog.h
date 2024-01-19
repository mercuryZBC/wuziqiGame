#ifndef GAMELOBBYDIALOG_H
#define GAMELOBBYDIALOG_H

#include <QDialog>
#include<QTimer>
#include<Kernel/Kernel.h>
#include"Config/ClientConfig.h"
#include"./friendWidgetItem/friendwidgetitem.h"
#include<QVBoxLayout>
#include"gameroomwidgetitem.h"
#include"gamedialog.h"
#include"logindialog.h"
namespace Ui {
class GameLobbyDialog;
}

class GameLobbyDialog : public QDialog
{
    Q_OBJECT
public:
    int m_iconId;
    QString m_userName;
    Kernel* m_pKernel;
    explicit GameLobbyDialog(QString userId,QWidget *parent = nullptr);
    explicit GameLobbyDialog(QWidget *parent = nullptr);
    ~GameLobbyDialog();
    void init();
private:
    QVBoxLayout* m_vbLayout;
    QGridLayout*  m_gridLayout;
    QMap<QString,CLIENT_FRIEND_INFO>m_mapFriendIdToInfo;
    QMap<QString,friendWidgetItem*>m_mapIdToFriendItem;
    QList<QPair<QString,friendWidgetItem*>>m_listFriendItem;
    QMap<int,GameRoomWidgetItem*>m_mapRoomIdToRoomItem;
private:
    QString m_userId;
    GameDialog* m_pGameDialog;
private:
    Ui::GameLobbyDialog *ui;
public:

public slots:
    void onLoginRq(QString userid,QString passwd);
    //登录结果到来
    void LoginRsComing(int state,int iconId,QString userName,QString feeling);
    //拉取好友列表
    void FriendInfoComing(int state,QString id,QString name,int iconId,QString feeling);

    void onFriendOnline(QString friendId);

    void createRoomRsComing(STRU_CREATE_ROOM_RS createRoomRs);

    void loadExistRoomRsComing(STRU_LOAD_EXIST_ROOM_RS loadExistRoomRs);
    void roomBeCloseComing(int roomId);
    void playerGameExitRoomComing(int roomId);
    void joinRoomComing(int roomId);
    void joinRoomRSComing(STRU_JOIN_ROOM_RS joinRoomRs);
    void readyGameComing(int roomId);



private slots:
    void on_pb_newMatch_clicked();
    void on_pb_quickStart_clicked();
    void on_pb_newRoom_clicked();
signals:
    void SIG_showMainWindow();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    LoginDialog* m_pLoginDialog =nullptr;
};

#endif // GAMELOBBYDIALOG_H
