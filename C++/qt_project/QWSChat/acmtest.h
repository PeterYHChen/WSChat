#ifndef ACMTEST_H
#define ACMTEST_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "login.h"
#include "QWsSocket.h"
namespace Ui {
class acmTest;
}

class QWSChat : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QWSChat(QWidget *parent = 0);
    bool loginSucceed();
    ~QWSChat();
    
private slots:
    void on_EnterButton_clicked();
    void displayMessage(QString s);
    void setLoginSocketLabel();
    void reconnectSocket();
private:
    Ui::acmTest *ui;
    QtWebsocket::QWsSocket* websocket;
    QString ip;
    quint16 port;
    Login* login;
    QTimer* timer;
    QString currentSocketState(QAbstractSocket::SocketState socketState);

};

#endif // ACMTEST_H
