#include <QtGui/QApplication>
#include "acmtest.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWSChat w;
    if(w.loginSucceed())
        w.show();
    
    return a.exec();
}
