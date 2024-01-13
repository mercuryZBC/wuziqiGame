/********************************************************************************
** Form generated from reading UI file 'playerinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERINFO_H
#define UI_PLAYERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerInfo
{
public:
    QLabel *lb_icon;
    QLabel *lb_name;
    QLabel *lb_remainderTimer;
    QLabel *lb_timer;
    QPushButton *pb_side;

    void setupUi(QWidget *PlayerInfo)
    {
        if (PlayerInfo->objectName().isEmpty())
            PlayerInfo->setObjectName(QString::fromUtf8("PlayerInfo"));
        PlayerInfo->resize(300, 424);
        lb_icon = new QLabel(PlayerInfo);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setGeometry(QRect(20, 10, 200, 200));
        lb_name = new QLabel(PlayerInfo);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(20, 210, 161, 41));
        QFont font;
        font.setPointSize(15);
        lb_name->setFont(font);
        lb_remainderTimer = new QLabel(PlayerInfo);
        lb_remainderTimer->setObjectName(QString::fromUtf8("lb_remainderTimer"));
        lb_remainderTimer->setGeometry(QRect(20, 275, 261, 41));
        lb_remainderTimer->setFont(font);
        lb_timer = new QLabel(PlayerInfo);
        lb_timer->setObjectName(QString::fromUtf8("lb_timer"));
        lb_timer->setGeometry(QRect(20, 340, 261, 41));
        lb_timer->setFont(font);
        pb_side = new QPushButton(PlayerInfo);
        pb_side->setObjectName(QString::fromUtf8("pb_side"));
        pb_side->setGeometry(QRect(230, 150, 60, 60));
        pb_side->setIconSize(QSize(60, 60));

        retranslateUi(PlayerInfo);

        QMetaObject::connectSlotsByName(PlayerInfo);
    } // setupUi

    void retranslateUi(QWidget *PlayerInfo)
    {
        PlayerInfo->setWindowTitle(QCoreApplication::translate("PlayerInfo", "Form", nullptr));
        lb_icon->setText(QString());
        lb_name->setText(QCoreApplication::translate("PlayerInfo", "name", nullptr));
        lb_remainderTimer->setText(QCoreApplication::translate("PlayerInfo", "\345\261\200\346\227\266\357\274\232 10\357\274\23200", nullptr));
        lb_timer->setText(QCoreApplication::translate("PlayerInfo", "\345\200\222\350\256\241\346\227\266\357\274\23210\357\274\23200", nullptr));
        pb_side->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlayerInfo: public Ui_PlayerInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERINFO_H
