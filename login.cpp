#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

extern bool isTourist;
extern QString UserName;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    cl = new chatClient(this);
    cl -> connectToServer("127.0.0.1", 6666);

    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(receive_signal(const QString&)));

    setWindowTitle(tr("Login"));
    setWindowIcon(QIcon(":/Chat.ico"));
}

login::~login()
{
    delete ui;
    if(cl != nullptr)
        delete cl;
}

void login::receive_signal(const QString& rmsg) {
    if(isTourist) {
        if(rmsg == "Accept") {
            accept();
            return ;
        } else {
            QMessageBox :: warning(this, tr("Warning"), tr("Something bad happens."), QMessageBox :: Yes);
            ui -> usrLineEdit -> clear();
            ui -> pwdLineEdit -> clear();
            return ;
        }
    }
    if(rmsg == "Accept") {
        accept();
        return ;
    }
    if(rmsg == "NoUser") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: No such user!"), QMessageBox :: Yes);
        ui -> usrLineEdit -> clear();
        ui -> pwdLineEdit -> clear();
        return ;
    }
    if(rmsg == "WrongPwd") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Wrong PassWord!"), QMessageBox :: Yes);
        ui -> pwdLineEdit -> clear();
        return ;
    }
}

void login::on_loginBtn_clicked()
{
    QString username = ui -> usrLineEdit -> text().trimmed();
    QString pwd = ui -> pwdLineEdit -> text();
    isTourist = 0;
    UserName = "Tourist";
    if(username.length() == 0 && pwd.length() == 0) {
        QString msg = "~@LoginRequest#Tourist";
        isTourist = 1;
        cl -> sendMessage(msg);
        return ;
    }
    if(username.length() < 3 || username.length() > 256) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usrLineEdit -> clear();
        ui -> pwdLineEdit -> clear();
        return ;
    }
    for (int i=0; i<username.length(); ++i) {
        if(username[i] >= 'a' && username[i] <= 'z') continue;
        if(username[i] >= 'A' && username[i] <= 'Z') continue;
        if(username[i] >= '0' && username[i] <= '9') continue;
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usrLineEdit -> clear();
        ui -> pwdLineEdit -> clear();
        return ;
    }
    if(username == "Tourist") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usrLineEdit -> clear();
        ui -> pwdLineEdit -> clear();
        return ;
    }
    UserName = username;

    if(pwd.length() > 16 || pwd.length() == 0) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should have length between 1 and 16!"), QMessageBox :: Yes);
        ui -> pwdLineEdit -> clear();
        return ;
    }
    for (int i=0; i<pwd.length(); ++i) {
        if(pwd[i] == '#') {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should not include \'#\'!"), QMessageBox :: Yes);
            ui -> pwdLineEdit -> clear();
            return ;
        }
    }

    QString msg = "~@LoginRequest#" + username + "#" + pwd;
    cl -> sendMessage(msg);
    return ;
}

void login::Disconnect() {
    cl -> disconnect();
}

void login::on_registerBtn_clicked()
{
    regist reg;
    reg.exec();
    reg.Disconnect();
}

void login::on_checkBox_stateChanged(int arg1)
{
    if(arg1) ui -> pwdLineEdit -> setEchoMode(QLineEdit :: Normal);
    else ui -> pwdLineEdit -> setEchoMode(QLineEdit :: Password);
}
