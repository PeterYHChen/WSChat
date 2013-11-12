#ifndef WSCHAT_H
#define WSCHAT_H

#include <QMainWindow>
#include "LoginDlg.h"
#include "QWebSocket_files/QWsSocket.h"

namespace Ui {
class WSChat;
}

class WSChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit WSChat(QWidget *parent = 0);
    ~WSChat();
    bool loginSucceed();


private:
    Ui::WSChat *ui;
    LoginDlg* login;
    QString ip;
    qint16 port;
    QString socketState;
    QtWebsocket::QWsSocket* websocket;
    QTimer* timer;
    int flag;
    int loginSuccess;

    void initiateWidgets();
    void initiateLoginDlg();
    void initiateWebSocket();
    void displayMessage(QString);
    QString currentSocketState(QAbstractSocket::SocketState socketState);

protected:
    void resizeEvent(QResizeEvent *);

signals:
    void setDlgSocketState(QString);

private slots:
    void on_enterButton_clicked();
    void checkSocketState();
    void reconnectSocket();
    void sendUserName(QString);
    void checkMessage(QString);
};

#endif // WSCHAT_H
