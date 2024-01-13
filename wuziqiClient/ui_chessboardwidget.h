/********************************************************************************
** Form generated from reading UI file 'chessboardwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSBOARDWIDGET_H
#define UI_CHESSBOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessboardWidget
{
public:

    void setupUi(QWidget *ChessboardWidget)
    {
        if (ChessboardWidget->objectName().isEmpty())
            ChessboardWidget->setObjectName(QString::fromUtf8("ChessboardWidget"));
        ChessboardWidget->resize(660, 660);
        ChessboardWidget->setMinimumSize(QSize(660, 660));
        ChessboardWidget->setMaximumSize(QSize(660, 660));
        ChessboardWidget->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(ChessboardWidget);

        QMetaObject::connectSlotsByName(ChessboardWidget);
    } // setupUi

    void retranslateUi(QWidget *ChessboardWidget)
    {
        ChessboardWidget->setWindowTitle(QCoreApplication::translate("ChessboardWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChessboardWidget: public Ui_ChessboardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSBOARDWIDGET_H
