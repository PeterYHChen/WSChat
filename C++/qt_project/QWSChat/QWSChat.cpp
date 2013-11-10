#include "QWSChat.h"
#include "ui_acmtest.h"
#include <QTimer>
#include <QTime>
#include <qjson/parser.h>
QWSChat::QWSChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acmTest)
{

    ui->setupUi(this);
    ui->textEdit->setFocus();
    ui->EnterButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_I));


    ip = "ws://tunnel.vince.im";
    port = 8999;
    websocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);
    websocket->connectToHost(ip.toUtf8(),port);
    QObject::connect(websocket, SIGNAL(frameReceived(QString)), this, SLOT(checkMessage(QString)));


    login = new Login(this);
    login->setLabel(currentSocketState(websocket->state()));
    login->show();
    QObject::connect(login,SIGNAL(requestReconnect()),this, SLOT(reconnectSocket()));
    QObject::connect(login,SIGNAL(sendUserName(QString)),this, SLOT(sendUserName(QString)));


    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setLoginSocketLabel()));
    timer->start(1000);

    flag = 1;
    loginSuccess = 0;
}



bool QWSChat::loginSucceed()
{
    if(login->exec() == QDialog::Accepted)
    {
        delete timer;
        timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkSocketState()));
        timer->start(1000);
        loginSuccess = 1;
        return true;
    }
    return false;
}

QWSChat::~QWSChat()
{
    //QMessageBox::warning(this, tr("23"), tr("fd"), QMessageBox::Yes);
    websocket->disconnectFromHost();
    delete ui;
}

void QWSChat::on_EnterButton_clicked()
{
    QString editText = ui->textEdit->toPlainText();

    if(editText.length() != 0)
    {
        if(websocket->state() != QAbstractSocket::ConnectedState)
            displayMessage("\nsocket is unconnected, please check your internet and reopen the window");
        else
        {
            ui->textEdit->clear();
            ui->textEdit->setFocus();
            websocket->write(editText);
        }

    }
}

void QWSChat::displayMessage(QString editText)
{
    ui->textBrowser->append(editText);

}

QString QWSChat::currentSocketState(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            return tr("Unconnected");

        case QAbstractSocket::HostLookupState:
            return tr("HostLookup");

        case QAbstractSocket::ConnectingState:
            return tr("Connecting");

        case QAbstractSocket::ConnectedState:
            return tr("Connected");

        case QAbstractSocket::BoundState:
            return tr("Bound");

        case QAbstractSocket::ClosingState:
            return tr("Closing");

        case QAbstractSocket::ListeningState:
            return tr("Listening");

        default:
            return tr("Unknown");
    }
}

void QWSChat::setLoginSocketLabel()
{
    login->setLabel(currentSocketState(websocket->state()));;
}

void QWSChat::reconnectSocket()
{
    delete websocket;
    ip = "ws://tunnel.vince.im";
    port = 8999;
    websocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);
    websocket->connectToHost(ip.toUtf8(),port);
    QObject::connect(websocket, SIGNAL(frameReceived(QString)), this, SLOT(checkMessage(QString)));

    if(!loginSuccess)
        login->setLabel(currentSocketState(websocket->state()));
}

void QWSChat::sendUserName(QString name)
{
        websocket->write(tr("/nick ") + name);
}

void QWSChat::checkMessage(QString msg)
{
    if(!loginSuccess)
    {
        if(msg == "nick:success")
            login->accept();
        else
        {
            QMessageBox::warning(login, tr("Oops~"), msg, QMessageBox::Yes);
        }
    }
    else
    {
        if(msg == "nick:success")
            displayMessage(tr("\tlogin success!"));
        else
            displayMessage(msg);
    }
}

void QWSChat::checkSocketState()
{

    if (websocket->state() == QAbstractSocket::ConnectedState)
    {
        if(flag == 1)
            return;
        else
        {
            QMessageBox::warning(this, tr("Yeah~"), tr("\nsocket is connected!"), QMessageBox::Yes);
            flag = 1;
            sendUserName(login->userName);
        }
    }
    else /* if(websocket->state() == QAbstractSocket::UnconnectedState)*/
    {
        if(flag == 1)
        {
            flag = 0;
            QMessageBox::warning(this, tr("Oops~"),
                                 tr("\nsocket is unconnected, please check your internet or reopen the window"),
                                 QMessageBox::Yes);
            reconnectSocket();
        }
        else
            reconnectSocket();
    }
}
