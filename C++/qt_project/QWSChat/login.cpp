#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
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
    if(userName != "")
        sendUserName(userName);
    else
         QMessageBox::warning(this, tr("Oops~"), tr("\n userName is empty"),QMessageBox::Yes);
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
