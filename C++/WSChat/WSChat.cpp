#include "WSChat.h"
#include "ui_WSChat.h"
#include <QTimer>
WSChat::WSChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WSChat)
{
    ui->setupUi(this);

    //initiate all the widgets' states
    initiateWidgets();

    initiateWebSocket();

    initiateLoginDlg();

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkSocketState()));
    timer->start(1000);

    flag = 1;
    loginSuccess = 0;
}

WSChat::~WSChat()
{
    delete websocket;
    delete timer;
    delete login;
    delete ui;
}

bool WSChat::loginSucceed()
{
    if(login->exec() == QDialog::Accepted)
        loginSuccess = 1;
    return loginSuccess;
}

void WSChat::initiateWidgets()
{
    // size of window can not be obtained when initialized
    //QSize mainSize(WSChat::size());

    //set the fixed size for each widgets if necessary
    ui->textEdit->setFixedHeight(110);
    ui->enterButton->setFixedSize(50, ui->textEdit->size().height());
    ui->infoLabel->setFixedHeight(16);

    ui->textEdit->setFocus();
    ui->enterButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_I));
}

void WSChat::initiateWebSocket()
{
    ip = "ws://localhost";
    port = 8999;
    websocket = new QtWebsocket::QWsSocket(this, NULL, QtWebsocket::WS_V13);
    websocket->connectToHost(ip.toUtf8(), port);
    QObject::connect(websocket, SIGNAL(frameReceived(QString)), this, SLOT(checkMessage(QString)));

    //set the socket state of dlg and main window
    socketState = currentSocketState(websocket->state());
    //QMessageBox::warning(this, tr(""), socketState, QMessageBox::Yes);
    ui->infoLabel->setText(socketState);

}

void WSChat::displayMessage(QString msg)
{
    ui->textBrowser->append(msg);
}

void WSChat::initiateLoginDlg()
{
    login = new LoginDlg(this);

    QObject::connect(login,SIGNAL(sendUserName(QString)),this, SLOT(sendUserName(QString)));
    QObject::connect(login,SIGNAL(requestReconnect()),this, SLOT(reconnectSocket()));
    QObject::connect(this,SIGNAL(setDlgSocketState(QString)),login, SLOT(setDlgSocketState(QString)));

    //can not close the process when close the login dialog
    setDlgSocketState(currentSocketState(websocket->state()));

    login->show();

}

QString WSChat::currentSocketState(QAbstractSocket::SocketState state)
{
    switch (state)
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

void WSChat::resizeEvent(QResizeEvent *e)
{
    //the width between widgets
    int w = 5;

    // get size of the window
    QSize mainSize(WSChat::size());

    //resize all the widgets according to the window size
    ui->textEdit->resize(mainSize.width() - ui->enterButton->width() - 3 * w, 110);
    ui->textEdit->move(w, mainSize.height() - (ui->textEdit->height() + ui->infoLabel->height() + 2 * w));

    ui->enterButton->move(mainSize.width() - w - ui->enterButton->width(),
                          mainSize.height() - (ui->enterButton->height() + ui->infoLabel->height() + 2 * w));

    ui->infoLabel->resize(ui->textEdit->size().width(), 16);
    ui->infoLabel->move(w, mainSize.height() - ui->infoLabel->height() - w - 2);

    ui->textBrowser->resize(mainSize.width() - 2 * w,
                            mainSize.height() - ui->textEdit->size().height() - ui->infoLabel->size().height() - 4 * w);
    ui->textBrowser->move(w, w);
}

void WSChat::on_enterButton_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if(text.length() != 0)
    {
        checkSocketState();
        if(socketState != tr("Connected"))
            ui->infoLabel->setText(tr("Socket is unconnected, please wait or reopen the window"));
        else
        {
            ui->textEdit->clear();
            ui->textEdit->setFocus();
            websocket->write(text);
        }
    }
}

void WSChat::checkSocketState()
{
    socketState = currentSocketState(websocket->state());
    ui->infoLabel->setText(socketState);
    //login->msgWarning("hhh");
    if(!loginSuccess)
        setDlgSocketState(socketState);
    else
    {
        if (socketState == tr("Connected"))
        {
            if(flag != 1)
            {
                flag = 1;
                sendUserName(login->getUserName());
            }
        }
        else /* if(websocket->state() == QAbstractSocket::UnconnectedState)*/
        {
            if(flag == 1)
            {
                flag = 0;
                QMessageBox::warning(this,tr(""),tr("socket is unconnected, please wait until it is connected"),
                                     QMessageBox::Yes);
            }
            reconnectSocket();
        }
    }
}

void WSChat::reconnectSocket()
{
    delete websocket;
    initiateWebSocket();

    if(!loginSuccess)
        setDlgSocketState(socketState);
}

void WSChat::sendUserName(QString userName)
{
    websocket->write(tr("/nick ") + userName);
}

void WSChat::checkMessage(QString msg)
{
    if(!loginSuccess)
    {
        if(msg == "nick:success")
            login->accept();
        else
        {
            msg = msg.remove(0,10);
            login->msgWarning(msg);
        }
    }
    else
    {
        if(msg == "nick:success")
            ui->infoLabel->setText(tr("Yeah~ Socket is connected!\tlogin success!"));
        else
            displayMessage(msg.toHtmlEscaped());
    }
}
