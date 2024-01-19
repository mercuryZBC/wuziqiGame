#include "mainwindow.h"
#include <QApplication>
#include<QMessageBox>
#include"Kernel/Kernel.h"
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QString userId = "";
    if(argc != 1){
        userId = argv[1];
    }
    MainWindow w(userId);
    w.show();
    return a.exec();
}
