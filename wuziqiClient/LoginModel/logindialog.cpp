#include "logindialog.h"
#include "ui_logindialog.h"
#include"./Config/config.h"
#include<QMessageBox>
#include<QDebug>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->le_passwd->setEchoMode(QLineEdit::Password);
    ui->le_registerPasswd->setEchoMode(QLineEdit::Password);
    ui->le_registerPasswdConfirm->setEchoMode(QLineEdit::Password);
    m_pKernel = Kernel::getInstance();
    connect(m_pKernel,&Kernel::SIG_Register,this,&LoginDialog::onRegisterResult);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::checkPasswdFromat(QString userId, QString passwd)
{

    if(userId.length()!=_DEF_PHONE_NUM_LEN||
            userId[0]!='1'){
        QMessageBox::warning(this,"warning","用户名格式错误");
        return false;
    }
    for(int i=0;i<userId.length();i++){
        if(userId[i]<'0'&&userId[i]>'9'){
            QMessageBox::warning(this,"warning","用户名格式错误");
            return false;
        }
    }
    if(passwd.length()<10||passwd.length()>20){
        QMessageBox::warning(this,"warning","密码格式错误");
        return false;
    }
    for(int i=0;i<passwd.length();i++){
        if(!((passwd[i]>='0'&&passwd[i]<='9')||
                (passwd[i]>='a'&&passwd[i]<='z')||
                (passwd[i]>='A'&&passwd[i]<='Z')||passwd[i]=='_')){
            QMessageBox::warning(this,"warning","密码格式错误");
            return false;
        }
    }
    return true;
}

bool LoginDialog::checkPasswdFromat(QString userId, QString passwd, QString passwdConfirm)
{
    if(userId.length()!=_DEF_PHONE_NUM_LEN||
            userId[0]!='1'){
        QMessageBox::warning(this,"warning","账号请输入11位手机号");
        return false;
    }
    for(int i=0;i<userId.length();i++){
        if(userId[i]<'0'&&userId[i]>'9'){
            QMessageBox::warning(this,"warning","账号请输入11位手机号");
            return false;
        }
    }
    if(passwd.length()<10||passwd.length()>20){
        QMessageBox::warning(this,"warning","密码格式错误");
        return false;
    }
    if(passwd != passwdConfirm){
        QMessageBox::warning(this,"warning","密码和确认密码不同");
        return false;
    }
    for(int i=0;i<passwd.length();i++){
        if(!((passwd[i]>='0'&&passwd[i]<='9')||
                (passwd[i]>='a'&&passwd[i]<='z')||
                (passwd[i]>='A'&&passwd[i]<='Z')||passwd[i]=='_')){
            QMessageBox::warning(this,"warning","密码格式错误");
            return false;
        }
    }
    return true;
}

void LoginDialog::on_pb_register_clicked()//注册
{
    qDebug()<<"text";
    QString reg_id=ui->le_register_Id->text();
    QString reg_name=ui->le_register_name->text();
    QString reg_passwd=ui->le_registerPasswd->text();
    QString reg_passwdConfirm=ui->le_registerPasswdConfirm->text();
    bool isTrue=checkPasswdFromat(reg_id,reg_passwd,reg_passwdConfirm);//检查手机号，密码格式是否正确
    if(isTrue==false){

        return;
    }
    m_pKernel->sendRegisterRq(reg_id,reg_name,reg_passwd);

}


void LoginDialog::on_pb_signIn_clicked()
{
    //规定用户名由数字组成，并且为11位
    userId=ui->le_userId->text();

    //规定密码由大小写字母，数字，下划线组成，并且小于20位
    QString userPasswd=ui->le_passwd->text();
    ui->le_userId->clear();//清空
    ui->le_passwd->clear();
    bool isTrue=checkPasswdFromat(userId,userPasswd);//检查手机号，密码格式是否正确
    if(isTrue==false){

        return;
    }
    emit SIG_SignIn(userId,userPasswd);//发送登录信号
}


void LoginDialog::on_pb_register_clear_clicked()//注册信息清空
{
    ui->le_register_Id->clear();
    ui->le_register_name->clear();
    ui->le_registerPasswd->clear();
}

void LoginDialog::onRegisterResult(int state)
{
    if(state==registerSuccess){
        QMessageBox::information(this,"information","register success");
    }
    else if(state==userIsExist){
        QMessageBox::warning(this,"warning","user is exist,register failed");
    }
    else{
        QMessageBox::warning(this,"warning","Server exception");
    }
    ui->le_register_name->clear();
    ui->le_register_Id->clear();
    ui->le_registerPasswd->clear();
    ui->le_registerPasswdConfirm->clear();
}



