#ifndef GAMEROOMWIDGETITEM_H
#define GAMEROOMWIDGETITEM_H

#include <QWidget>
#include"Config/config.h"
namespace Ui {
class GameRoomWidgetItem;
}

class GameRoomWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit GameRoomWidgetItem(STRU_LOAD_EXIST_ROOM_RS& pack,QWidget *parent = nullptr);
    ~GameRoomWidgetItem();
    void setIcon();
    void updateRoomState(STRU_LOAD_EXIST_ROOM_RS& pack);
private slots:
    void on_pb_user1Icon_clicked();
    void on_pb_user2Icon_clicked();
signals:
    void SIG_joinGameRoom(int roomId);
private:
    Ui::GameRoomWidgetItem *ui;
public:
    int m_roomId;
    QString m_user1Id;
    QString m_user2Id;
    int m_user1IconId;
    int m_user2IconId;
    bool state;//游戏状态,0代表wait,1代表start
};

#endif // GAMEROOMWIDGETITEM_H
