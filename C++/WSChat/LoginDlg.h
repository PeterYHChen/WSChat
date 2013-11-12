#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();
    QString getUserName();
    void msgWarning(QString msg);

signals:
    void sendUserName(QString name);
    void requestReconnect();

private slots:
    void on_loginButton_clicked();
    void on_connectButton_clicked();
    void setDlgSocketState(QString);

private:
    Ui::LoginDlg *ui;
    QString userName;
    QString socketState;

};

#endif // LOGINDLG_H
