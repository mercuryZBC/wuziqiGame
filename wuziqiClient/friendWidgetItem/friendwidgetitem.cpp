#include "friendwidgetitem.h"
#include "ui_friendwidgetitem.h"
#include<QBitmap>
friendWidgetItem::friendWidgetItem(CLIENT_FRIEND_INFO struFriendInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendWidgetItem)
{

    ui->setupUi(this);
    this->id=struFriendInfo.id;
    this->name=struFriendInfo.name;
    this->iconId=struFriendInfo.iconId;
    this->feeling=struFriendInfo.feeling;
    this->state = struFriendInfo.state;
    ui->lable_name->setText(name);
    ui->lable_feeling->setText(feeling);

//    m_pChatDialog = new ChatDialog(struFriendInfo,this);//创建聊天窗口
//    //m_pChatDialog=new ChatDialog(name,this);
//    connect(m_pChatDialog,&ChatDialog::SIG_chatMsg,this,&friendWidgetItem::onSendChatMsg);
//    connect(m_pChatDialog,&ChatDialog::SIG_sendFile,this,&friendWidgetItem::onSendfile);
//    connect(m_pChatDialog,&ChatDialog::SIG_sendFileRequest,this,&friendWidgetItem::onSendFileRequest);
//    connect(m_pChatDialog,&ChatDialog::SIG_recvFileRequst,this,&friendWidgetItem::onRecvFileRequestFromChatDialog);
    QString iconPath=QString(":/res/tx/%1.png").arg(this->iconId);
    if(state==online){
        ui->pb_icon->setIcon(QIcon(iconPath));
        qDebug()<<this->name<<" is online";
    }
    else if(state==offline){
        QBitmap bmp;
        bmp.load(iconPath);
        ui->pb_icon->setIcon(bmp);
        qDebug()<<this->name<<" is offline";
    }
    repaint();
    //show();
}

//friendWidgetItem::friendWidgetItem(int state,QString id,QString name,int iconId,QString feeling,QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::friendWidgetItem)
//{

//    ui->setupUi(this);
//    this->id=id;
//    this->name=name;
//    this->iconId=iconId;
//    this->feeling=feeling;
//    ui->lable_name->setText(name);
//    ui->lable_feeling->setText(feeling);
//    CLIENT_FRIEND_INFO struFriendInfo;
//    strncpy(struFriendInfo.id,this->id.toStdString().c_str(),this->id.length());
//    strncpy(struFriendInfo.name,this->name.toStdString().c_str(),this->name.length());
//    struFriendInfo.iconId = this->iconId;
//    m_pChatDialog = new ChatDialog(struFriendInfo,this);//创建聊天窗口
//    //m_pChatDialog=new ChatDialog(name,this);
//    connect(m_pChatDialog,&ChatDialog::SIG_chatMsg,this,&friendWidgetItem::onSendChatMsg);
//    connect(m_pChatDialog,&ChatDialog::SIG_sendFile,this,&friendWidgetItem::onSendfile);
//    connect(m_pChatDialog,&ChatDialog::SIG_sendFileRequest,this,&friendWidgetItem::onSendFileRequest);
//    connect(m_pChatDialog,&ChatDialog::SIG_recvFileRequst,this,&friendWidgetItem::onRecvFileRequestFromChatDialog);
//    QString iconPath=QString(":/tx/%1.png").arg(iconId);
//    if(state==online){
//         ui->pb_icon->setIcon(QIcon(iconPath));
//         qDebug()<<this->name<<" is online";
//    }
//    else if(state==offline){
//            QBitmap bmp;
//            bmp.load(iconPath);
//            ui->pb_icon->setIcon(bmp);
//            qDebug()<<this->name<<" is offline";
//    }
//    repaint();
//    //show();
//}

friendWidgetItem::~friendWidgetItem()
{
    //delete m_pChatDialog;
    delete ui;

}

void friendWidgetItem::setOnline()
{
        qDebug()<<__func__;
        state=online;
        QString iconPath=QString(":/tx/%1.png").arg(iconId);
        ui->pb_icon->setIcon(QIcon(iconPath));
        qDebug()<<this->name<<" is online";
        repaint();
}

void friendWidgetItem::chatDataCome(QString chatData)
{
    qDebug()<<"friendWidgetItem::chatDataCome";
        //m_pChatDialog->setChatText(chatData);
}

void friendWidgetItem::friendsFileComing(CLIENT_FILE_INFO clientFileInfo)
{
        qDebug()<<"friendWidgetItem::friendsFileComing";
        //m_pChatDialog->friendFileComing(clientFileInfo);
}

QString friendWidgetItem::getName()
{
    return name;
}

int friendWidgetItem::getIconId()
{
    return iconId;
}

void friendWidgetItem::on_pb_icon_clicked()
{
    //m_pChatDialog->show();
}

void friendWidgetItem::onSendChatMsg(QString chatData)
{
    qDebug()<<"friendWidgetItem::onSendChatMsg";
    STRU_CHAT_RQ chatRqPack;
    memset(chatRqPack.chatDate,0,sizeof(chatRqPack.chatDate));
    memset(chatRqPack.friendId,0,sizeof(chatRqPack.friendId));
    int nLen=id.length();
    strncpy(chatRqPack.friendId,id.toStdString().c_str(),nLen);//将文本消息放入包中
    strcpy_s(chatRqPack.chatDate,chatData.toStdString().c_str());//将好友id放入包中
    emit SIG_itemSendChatMeg(chatRqPack);

}
