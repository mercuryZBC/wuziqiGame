#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"Kernel/Kernel.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    QString userId;
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
public:
    bool checkPasswdFromat(QString userId,QString passwd);
    bool checkPasswdFromat(QString userId,QString passwd,QString passwdConfirm);
signals:
    void SIG_SignIn(QString,QString);
    void SIG_Register(QString id,QString name,QString passwd);
private slots:
    void on_pb_register_clicked();

    void on_pb_signIn_clicked();

    void on_pb_register_clear_clicked();
    //注册结果到来

public slots:
    void onRegisterResult(int state);
private:
    Kernel *m_pKernel;
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
