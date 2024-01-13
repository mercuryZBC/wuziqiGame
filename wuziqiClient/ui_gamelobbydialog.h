/********************************************************************************
** Form generated from reading UI file 'gamelobbydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMELOBBYDIALOG_H
#define UI_GAMELOBBYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameLobbyDialog
{
public:
    QTabWidget *tw_friend;
    QWidget *friendList;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QWidget *wdg_friendList;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_icon;
    QLabel *lable_name;
    QLineEdit *le_feeling;
    QPushButton *pb_newRoom;
    QPushButton *pb_quickStart;
    QTabWidget *tw_matchLobby;
    QWidget *tab;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_roomList;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *GameLobbyDialog)
    {
        if (GameLobbyDialog->objectName().isEmpty())
            GameLobbyDialog->setObjectName(QString::fromUtf8("GameLobbyDialog"));
        GameLobbyDialog->resize(1240, 887);
        tw_friend = new QTabWidget(GameLobbyDialog);
        tw_friend->setObjectName(QString::fromUtf8("tw_friend"));
        tw_friend->setGeometry(QRect(740, 10, 490, 851));
        QFont font;
        font.setPointSize(15);
        tw_friend->setFont(font);
        friendList = new QWidget();
        friendList->setObjectName(QString::fromUtf8("friendList"));
        scrollArea = new QScrollArea(friendList);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(-10, -10, 501, 851));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 499, 849));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wdg_friendList = new QWidget(scrollAreaWidgetContents_2);
        wdg_friendList->setObjectName(QString::fromUtf8("wdg_friendList"));

        verticalLayout->addWidget(wdg_friendList);

        verticalSpacer = new QSpacerItem(20, 820, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents_2);
        tw_friend->addTab(friendList, QString());
        pb_icon = new QPushButton(GameLobbyDialog);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(10, 10, 120, 120));
        pb_icon->setIconSize(QSize(120, 120));
        lable_name = new QLabel(GameLobbyDialog);
        lable_name->setObjectName(QString::fromUtf8("lable_name"));
        lable_name->setGeometry(QRect(140, 10, 281, 71));
        QFont font1;
        font1.setPointSize(20);
        lable_name->setFont(font1);
        le_feeling = new QLineEdit(GameLobbyDialog);
        le_feeling->setObjectName(QString::fromUtf8("le_feeling"));
        le_feeling->setGeometry(QRect(140, 90, 281, 41));
        QFont font2;
        font2.setPointSize(9);
        le_feeling->setFont(font2);
        pb_newRoom = new QPushButton(GameLobbyDialog);
        pb_newRoom->setObjectName(QString::fromUtf8("pb_newRoom"));
        pb_newRoom->setGeometry(QRect(10, 140, 191, 61));
        pb_newRoom->setFont(font1);
        pb_quickStart = new QPushButton(GameLobbyDialog);
        pb_quickStart->setObjectName(QString::fromUtf8("pb_quickStart"));
        pb_quickStart->setGeometry(QRect(210, 140, 211, 61));
        pb_quickStart->setFont(font1);
        tw_matchLobby = new QTabWidget(GameLobbyDialog);
        tw_matchLobby->setObjectName(QString::fromUtf8("tw_matchLobby"));
        tw_matchLobby->setGeometry(QRect(10, 210, 721, 651));
        tw_matchLobby->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea_2 = new QScrollArea(tab);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 703, 600));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        wdg_roomList = new QWidget(scrollAreaWidgetContents_3);
        wdg_roomList->setObjectName(QString::fromUtf8("wdg_roomList"));

        verticalLayout_2->addWidget(wdg_roomList);

        verticalSpacer_2 = new QSpacerItem(20, 571, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        gridLayout->addWidget(scrollArea_2, 1, 0, 1, 1);

        tw_matchLobby->addTab(tab, QString());

        retranslateUi(GameLobbyDialog);

        tw_friend->setCurrentIndex(0);
        tw_matchLobby->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GameLobbyDialog);
    } // setupUi

    void retranslateUi(QDialog *GameLobbyDialog)
    {
        GameLobbyDialog->setWindowTitle(QCoreApplication::translate("GameLobbyDialog", "Dialog", nullptr));
        tw_friend->setTabText(tw_friend->indexOf(friendList), QCoreApplication::translate("GameLobbyDialog", "\345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
        pb_icon->setText(QString());
        lable_name->setText(QCoreApplication::translate("GameLobbyDialog", "TextLabel", nullptr));
        pb_newRoom->setText(QCoreApplication::translate("GameLobbyDialog", "\346\226\260\345\273\272\346\210\277\351\227\264", nullptr));
        pb_quickStart->setText(QCoreApplication::translate("GameLobbyDialog", "\345\277\253\351\200\237\345\214\271\351\205\215", nullptr));
        tw_matchLobby->setTabText(tw_matchLobby->indexOf(tab), QCoreApplication::translate("GameLobbyDialog", "\345\257\271\345\261\200\345\244\247\345\216\205", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameLobbyDialog: public Ui_GameLobbyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMELOBBYDIALOG_H
