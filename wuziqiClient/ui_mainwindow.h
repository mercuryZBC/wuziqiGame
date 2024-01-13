/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pb_online;
    QPushButton *pb_pvp;
    QPushButton *pb_pve;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(604, 379);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pb_online = new QPushButton(centralwidget);
        pb_online->setObjectName(QString::fromUtf8("pb_online"));
        pb_online->setGeometry(QRect(170, 170, 251, 111));
        QFont font;
        font.setPointSize(20);
        pb_online->setFont(font);
        pb_pvp = new QPushButton(centralwidget);
        pb_pvp->setObjectName(QString::fromUtf8("pb_pvp"));
        pb_pvp->setGeometry(QRect(50, 30, 211, 111));
        pb_pvp->setFont(font);
        pb_pve = new QPushButton(centralwidget);
        pb_pve->setObjectName(QString::fromUtf8("pb_pve"));
        pb_pve->setGeometry(QRect(330, 30, 211, 111));
        pb_pve->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 604, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pb_online->setText(QCoreApplication::translate("MainWindow", "\345\234\250\347\272\277\345\257\271\345\261\200", nullptr));
        pb_pvp->setText(QCoreApplication::translate("MainWindow", "\347\216\251\345\256\266\345\257\271\346\210\230", nullptr));
        pb_pve->setText(QCoreApplication::translate("MainWindow", "\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
