#ifndef FRIENDWIDGETITEM_H
#define FRIENDWIDGETITEM_H

#include <QWidget>
#include"Config/Config.h"
#include<QDebug>
#include"Config/ClientConfig.h"
namespace Ui {
class friendWidgetItem;
}

class friendWidgetItem : public QWidget
{
    Q_OBJECT

private:
    int state;
    QString id;
    QString name;
    int iconId;
    QString feeling;
public:
    explicit friendWidgetItem(CLIENT_FRIEND_INFO struFriendInfo,QWidget *parent = nullptr);
    ~friendWidgetItem();
    void setOnline();//设置好友为在线
    QString getName();
    int getIconId();
signals:
    void SIG_itemSendChatMeg(STRU_CHAT_RQ);
    void SIG_itemSendFile(int filesize,QString fileName,char* buff,int nLen,QString id);
    void SIG_itemSendFileRequest(CLIENT_FILE_INFO);
    void SIG_itemRecvFileRequest(CLIENT_FILE_INFO);
private slots:
    void on_pb_icon_clicked();
private:
    Ui::friendWidgetItem *ui;
};

#endif // FRIENDWIDGETITEM_H
