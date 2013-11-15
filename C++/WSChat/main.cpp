#include "WSChat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WSChat w;

    if (w.loginSucceed())
        w.show();

    return a.exec();
}
