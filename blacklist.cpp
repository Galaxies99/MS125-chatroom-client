#include "blacklist.h"
#include "ui_blacklist.h"
#include <QMessageBox>

extern QString ipAddr;
extern int portAddr;
extern QString UserName;

blacklist::blacklist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::blacklist)
{
    ui->setupUi(this);
    cl = new chatClient(this);
    cl -> connectToServer(ipAddr, portAddr);

    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(receive_signal(const QString&)));
    setWindowTitle(tr("Change Account"));
    setWindowIcon(QIcon(":/Chat.ico"));
}

blacklist::~blacklist()
{
    delete ui;
    if(cl != nullptr) delete cl;
}


void blacklist::receive_signal(const QString& rmsg) {
    if(rmsg == "AcceptBlack") {
        QMessageBox :: information(this, tr("Information"), tr("Add to black list successfully."), QMessageBox :: Yes);
        ui -> blackEdit -> clear();
        return ;
    }
    if(rmsg == "AcceptWhite") {
        QMessageBox :: information(this, tr("Information"), tr("remove from black list successfully."), QMessageBox :: Yes);
        ui -> whiteEdit -> clear();
        return ;
    }
    if(rmsg == "NoUserBlack") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: No such user!"), QMessageBox :: Yes);
        ui -> blackEdit -> clear();
        return ;
    }
    if(rmsg == "NoUserWhite") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: No such user in your black list!"), QMessageBox :: Yes);
        ui -> whiteEdit -> clear();
        return ;
    }
}

void blacklist::on_addBtn_clicked()
{
    QString username = ui -> blackEdit -> text().trimmed();
    if(username.length() < 3 || username.length() > 256) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> blackEdit -> clear();
        return ;
    }
    for (int i=0; i<username.length(); ++i) {
        if(username[i] >= 'a' && username[i] <= 'z') continue;
        if(username[i] >= 'A' && username[i] <= 'Z') continue;
        if(username[i] >= '0' && username[i] <= '9') continue;
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> blackEdit -> clear();
        return ;
    }
    if(username.left(7) == "Tourist" && username != "Tourist") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> blackEdit -> clear();
        return ;
    }
    QString msg = "~@BlackList#" + UserName + "#" + username;
    cl -> sendMessage(msg);
}


void blacklist::on_removeBtn_clicked()
{
    QString username = ui -> whiteEdit -> text().trimmed();
    if(username.length() < 3 || username.length() > 256) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> whiteEdit -> clear();
        return ;
    }
    for (int i=0; i<username.length(); ++i) {
        if(username[i] >= 'a' && username[i] <= 'z') continue;
        if(username[i] >= 'A' && username[i] <= 'Z') continue;
        if(username[i] >= '0' && username[i] <= '9') continue;
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> whiteEdit -> clear();
        return ;
    }
    if(username.left(7) == "Tourist" && username != "Tourist") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> whiteEdit -> clear();
        return ;
    }
    QString msg = "~@WhiteList#" + UserName + "#" + username;
    cl -> sendMessage(msg);
}
