#include "startdialog.h"
#include "ui_startdialog.h"

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);
}

startDialog::~startDialog()
{
    delete ui;
}
