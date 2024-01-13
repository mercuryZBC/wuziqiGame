#include "playerinfo.h"
#include "ui_playerinfo.h"

PlayerInfo::PlayerInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
}

PlayerInfo::PlayerInfo(QString playerName, int playerIconId, QWidget *parent):
    QWidget(parent),
    ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
}

void PlayerInfo::setPlayerInfo(QString playerName, int playerIconId,bool isBlackPlayer)
{
    m_playerName = playerName;
    m_iconId = playerIconId;
    m_isBlackPlayer = isBlackPlayer;
    ui->lb_name->setText(m_playerName);
    QString iconPath=QString(":/res/tx/%1.png").arg(m_iconId);
    QImage image(iconPath);
    ui->lb_icon->setPixmap(QPixmap::fromImage(image).scaled(ui->lb_icon->size()));
    ui->lb_name->setText(m_playerName);
    if(isBlackPlayer == true) iconPath = QString(":/res/image/black.png");
    else{
      iconPath = QString(":/res/image/write.png");
    }
    ui->pb_side->setIcon(QIcon(iconPath));
}

void PlayerInfo::setRemainTime(int min, int sec)
{
    ui->lb_remainderTimer->setText(QString("局时： %1：%2").arg(min).arg(sec));
}

void PlayerInfo::setSide(bool isBlack)
{
    QString iconPath;
    if(isBlack) iconPath = QString(":/res/image/black.png");
    else{
      iconPath = QString(":/res/image/write.png");
    }
    ui->pb_side->setIcon(QIcon(iconPath));
}

PlayerInfo::~PlayerInfo()
{
    delete ui;
}
