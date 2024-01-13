/********************************************************************************
** Form generated from reading UI file 'friendwidgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDWIDGETITEM_H
#define UI_FRIENDWIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_friendWidgetItem
{
public:
    QLabel *lable_name;
    QLabel *lable_feeling;
    QPushButton *pb_icon;

    void setupUi(QWidget *friendWidgetItem)
    {
        if (friendWidgetItem->objectName().isEmpty())
            friendWidgetItem->setObjectName(QString::fromUtf8("friendWidgetItem"));
        friendWidgetItem->resize(490, 100);
        friendWidgetItem->setMinimumSize(QSize(490, 100));
        friendWidgetItem->setMaximumSize(QSize(490, 100));
        lable_name = new QLabel(friendWidgetItem);
        lable_name->setObjectName(QString::fromUtf8("lable_name"));
        lable_name->setGeometry(QRect(150, 10, 171, 41));
        QFont font;
        font.setPointSize(20);
        lable_name->setFont(font);
        lable_feeling = new QLabel(friendWidgetItem);
        lable_feeling->setObjectName(QString::fromUtf8("lable_feeling"));
        lable_feeling->setGeometry(QRect(150, 60, 250, 31));
        QFont font1;
        font1.setPointSize(13);
        lable_feeling->setFont(font1);
        pb_icon = new QPushButton(friendWidgetItem);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(20, 10, 80, 80));
        pb_icon->setIconSize(QSize(80, 80));

        retranslateUi(friendWidgetItem);

        QMetaObject::connectSlotsByName(friendWidgetItem);
    } // setupUi

    void retranslateUi(QWidget *friendWidgetItem)
    {
        friendWidgetItem->setWindowTitle(QCoreApplication::translate("friendWidgetItem", "Form", nullptr));
        lable_name->setText(QCoreApplication::translate("friendWidgetItem", "\346\210\221\346\230\257\350\260\201", nullptr));
        lable_feeling->setText(QCoreApplication::translate("friendWidgetItem", "\345\210\206\344\272\253\347\224\237\346\264\273\347\225\231\344\275\217\346\204\237\345\212\250", nullptr));
        pb_icon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class friendWidgetItem: public Ui_friendWidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDWIDGETITEM_H
