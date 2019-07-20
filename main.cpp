#include "mainwindow.h"
#include "login.h"
#include <QApplication>

bool isTourist;
QString UserName;

int main(int argc, char *argv[])
{
    isTourist = 0;
    QApplication a(argc, argv);
    MainWindow w;
    login dlg;
    if(dlg.exec() == QDialog :: Accepted) {
        dlg.Disconnect();
        if(isTourist) UserName = "Tourist";
        w.show();
        return a.exec();
    } else return 0;
}