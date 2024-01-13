/********************************************************************************
** Form generated from reading UI file 'gameroomwidgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEROOMWIDGETITEM_H
#define UI_GAMEROOMWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameRoomWidgetItem
{
public:
    QPushButton *pb_user1Icon;
    QPushButton *pb_user2Icon;
    QPushButton *pushButton;
    QLabel *lb_roomId;

    void setupUi(QWidget *GameRoomWidgetItem)
    {
        if (GameRoomWidgetItem->objectName().isEmpty())
            GameRoomWidgetItem->setObjectName(QString::fromUtf8("GameRoomWidgetItem"));
        GameRoomWidgetItem->resize(655, 124);
        GameRoomWidgetItem->setMinimumSize(QSize(655, 112));
        pb_user1Icon = new QPushButton(GameRoomWidgetItem);
        pb_user1Icon->setObjectName(QString::fromUtf8("pb_user1Icon"));
        pb_user1Icon->setGeometry(QRect(20, 10, 80, 80));
        pb_user1Icon->setIconSize(QSize(80, 80));
        pb_user2Icon = new QPushButton(GameRoomWidgetItem);
        pb_user2Icon->setObjectName(QString::fromUtf8("pb_user2Icon"));
        pb_user2Icon->setGeometry(QRect(110, 10, 80, 80));
        pb_user2Icon->setIconSize(QSize(80, 80));
        pushButton = new QPushButton(GameRoomWidgetItem);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(469, 20, 171, 71));
        lb_roomId = new QLabel(GameRoomWidgetItem);
        lb_roomId->setObjectName(QString::fromUtf8("lb_roomId"));
        lb_roomId->setGeometry(QRect(210, 30, 231, 41));
        QFont font;
        font.setPointSize(15);
        lb_roomId->setFont(font);

        retranslateUi(GameRoomWidgetItem);

        QMetaObject::connectSlotsByName(GameRoomWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *GameRoomWidgetItem)
    {
        GameRoomWidgetItem->setWindowTitle(QCoreApplication::translate("GameRoomWidgetItem", "Form", nullptr));
        pb_user1Icon->setText(QString());
        pb_user2Icon->setText(QString());
        pushButton->setText(QCoreApplication::translate("GameRoomWidgetItem", "\350\277\233\345\205\245\346\210\277\351\227\264", nullptr));
        lb_roomId->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameRoomWidgetItem: public Ui_GameRoomWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEROOMWIDGETITEM_H
