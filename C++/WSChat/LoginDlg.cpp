#include "LoginDlg.h"
#include "ui_LoginDlg.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    setFixedSize(400, 130);
    ui->nameInputLineEdit->setFocus();
}

LoginDlg::~LoginDlg()
{

    delete ui;
}

QString LoginDlg::getUserName()
{
    return userName;
}

void LoginDlg::setDlgSocketState(QString state)
{
    socketState = state;
    //show in the label
    ui->socketStateLabel->setText(socketState);
}

void LoginDlg::on_loginButton_clicked()
{
    if(socketState != tr("Connected"))
    {
        msgWarning(tr("\n Please wait until it is connected"));
        return;
    }

    userName = ui->nameInputLineEdit->text();
    if(userName == "")
    {
        msgWarning(tr("Empty username"));
        return;
    }
    else if(userName.length() > 10)
    {
        msgWarning(tr("username should not be over 10 characters"));
        return;
    }

    sendUserName(userName);
}


void LoginDlg::on_connectButton_clicked()
{
    ui->nameInputLineEdit->setFocus();

    if(socketState == tr("Connecting"))
        msgWarning(tr("Be Patient"));

    else if(socketState == tr("Connected"))
        msgWarning(tr("Don't be naughty, it is connected~"));
    else
    {
        requestReconnect();
        return;
    }
}


void LoginDlg::msgWarning(QString warningMsg)
{
    QMessageBox::warning(this, tr("Oops~"), warningMsg, QMessageBox::Yes);
    ui->nameInputLineEdit->setFocus();
}

