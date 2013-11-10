#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    if(ui->socketStateLabel->text() != tr("Connected"))
    {
        QMessageBox::warning(this, tr("Oops~"), tr("\n Please wait until it is connected"),QMessageBox::Yes);
        return;
    }

    userName = ui->usrLineEdit->text();
    password = ui->pwdLineEdit->text();

    if(userName == "yychan" && password == "gaojingwen")
        accept();
    else
    {
        QMessageBox::warning(this, tr("warning"), tr("username or password is wrong"), QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
    }
}

void Login::setLabel(QString text)
{
    ui->socketStateLabel->setText(text);
}

void Login::on_connectButton_clicked()
{
    QString text = ui->socketStateLabel->text();
    QString temp;
    if(text == tr("Connecting"))
        temp = tr("Be Patient");
    else if(text == tr("Connected"))
        temp = tr("Don't be naughty, it is connected~");
    else
    {
        requestReconnect();
        return;
    }
    QMessageBox::warning(this, tr("---"), temp, QMessageBox::Yes);

}
