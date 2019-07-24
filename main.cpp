#include "mainwindow.h"
#include "login.h"
#include <QApplication>

bool isTourist;
QString UserName;
QString ipAddr;
int portAddr;

int main(int argc, char *argv[])
{
    isTourist = 0;
    QApplication a(argc, argv);
    login dlg;
    if(dlg.exec() == QDialog :: Accepted) {
        dlg.Disconnect();
        MainWindow w;
        w.show();
        return a.exec();
    } else return 0;
}
