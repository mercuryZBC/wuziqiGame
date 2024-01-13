#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QWidget>
#include<QTimer>
namespace Ui {
class PlayerInfo;
}

class PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    bool m_isBlackPlayer;//是黑色方还是白色方
    explicit PlayerInfo(QWidget *parent = nullptr);
    explicit PlayerInfo(QString playerName,int playerIconId,QWidget *parent = nullptr);
    void setPlayerInfo(QString playerName,int playerIconId,bool isBlack);
    void setRemainTime(int min,int sec);
    void setSide(bool isBlack);
    ~PlayerInfo();
private:
    QString m_playerName;
    int m_iconId;
private:
    Ui::PlayerInfo *ui;
};

#endif // PLAYERINFO_H
