#include "acmtest.h"
#include "ui_acmtest.h"
#include <QTimer>
#include <QTime>

QWSChat::QWSChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acmTest)
{

    ui->setupUi(this);
    ui->textEdit->setFocus();
    ui->EnterButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_I));


    ip = "ws://localhost";
    port = 8999;
    websocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);
    websocket->connectToHost(ip.toUtf8(),port);

    QObject::connect(websocket, SIGNAL(frameReceived(QString)), this, SLOT(displayMessage(QString)));
    //QObject::connect(login, SIGNAL())

    login = new Login(this);
    login->setLabel(currentSocketState(websocket->state()));
    login->show();
    QObject::connect(login,SIGNAL(requestReconnect()),this, SLOT(reconnectSocket()));

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setLoginSocketLabel()));
    timer->start(1000);

}



bool QWSChat::loginSucceed()
{
    if(login->exec() == QDialog::Accepted)
    {
        delete timer;
        return true;
    }
    return false;
}

QWSChat::~QWSChat()
{
    websocket->disconnectFromHost();
    delete ui;
}

void QWSChat::on_EnterButton_clicked()
{
    QString editText = ui->textEdit->toPlainText();

    if(editText.length() != 0)
    {
        ui->textEdit->clear();
        ui->textEdit->setFocus();
        websocket->write("websocket "+ login->userName + "\n    " + editText);
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
    ip = "ws://localhost";
    port = 8999;
    websocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);
    websocket->connectToHost(ip.toUtf8(),port);
    QObject::connect(websocket, SIGNAL(frameReceived(QString)), this, SLOT(displayMessage(QString)));
    login->setLabel(currentSocketState(websocket->state()));
}
