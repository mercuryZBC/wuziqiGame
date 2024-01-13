/********************************************************************************
** Form generated from reading UI file 'startdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTDIALOG_H
#define UI_STARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_startDialog
{
public:

    void setupUi(QDialog *startDialog)
    {
        if (startDialog->objectName().isEmpty())
            startDialog->setObjectName(QString::fromUtf8("startDialog"));
        startDialog->resize(636, 389);

        retranslateUi(startDialog);

        QMetaObject::connectSlotsByName(startDialog);
    } // setupUi

    void retranslateUi(QDialog *startDialog)
    {
        startDialog->setWindowTitle(QCoreApplication::translate("startDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class startDialog: public Ui_startDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTDIALOG_H
