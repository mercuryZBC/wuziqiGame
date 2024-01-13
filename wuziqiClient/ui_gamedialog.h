/********************************************************************************
** Form generated from reading UI file 'gamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEDIALOG_H
#define UI_GAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameDialog
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *wdg_qipan;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_player1;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *wdg_player2;
    QPushButton *pb_startGame;

    void setupUi(QDialog *GameDialog)
    {
        if (GameDialog->objectName().isEmpty())
            GameDialog->setObjectName(QString::fromUtf8("GameDialog"));
        GameDialog->resize(1500, 987);
        scrollArea = new QScrollArea(GameDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(390, 40, 700, 700));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 698, 698));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wdg_qipan = new QWidget(scrollAreaWidgetContents);
        wdg_qipan->setObjectName(QString::fromUtf8("wdg_qipan"));

        verticalLayout->addWidget(wdg_qipan);

        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(GameDialog);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(30, 40, 351, 450));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 349, 448));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        wdg_player1 = new QWidget(scrollAreaWidgetContents_2);
        wdg_player1->setObjectName(QString::fromUtf8("wdg_player1"));

        verticalLayout_2->addWidget(wdg_player1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        scrollArea_3 = new QScrollArea(GameDialog);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(30, 520, 351, 450));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 349, 448));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        wdg_player2 = new QWidget(scrollAreaWidgetContents_3);
        wdg_player2->setObjectName(QString::fromUtf8("wdg_player2"));

        verticalLayout_3->addWidget(wdg_player2);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);
        pb_startGame = new QPushButton(GameDialog);
        pb_startGame->setObjectName(QString::fromUtf8("pb_startGame"));
        pb_startGame->setGeometry(QRect(510, 810, 511, 121));
        QFont font;
        font.setPointSize(40);
        pb_startGame->setFont(font);

        retranslateUi(GameDialog);

        QMetaObject::connectSlotsByName(GameDialog);
    } // setupUi

    void retranslateUi(QDialog *GameDialog)
    {
        GameDialog->setWindowTitle(QCoreApplication::translate("GameDialog", "Dialog", nullptr));
        pb_startGame->setText(QCoreApplication::translate("GameDialog", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameDialog: public Ui_GameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEDIALOG_H
