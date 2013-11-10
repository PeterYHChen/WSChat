#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void setLabel(QString text);
    QString userName;

signals:
    void requestReconnect();

private slots:
    void on_loginButton_clicked();
    void on_connectButton_clicked();

private:
    Ui::Login *ui;

    QString password;

};

#endif // LOGIN_H