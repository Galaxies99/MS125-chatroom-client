#include "change.h"
#include "ui_change.h"
#include <QMessageBox>

extern QString UserName;

change::change(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);
    cl = new chatClient(this);

    cl -> connectToServer("127.0.0.1", 6666);
    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(receive_signal(const QString&)));
    setWindowTitle(tr("Change Account"));
    setWindowIcon(QIcon(":/Chat.ico"));
}

change::~change()
{
    delete ui;
    if(cl != nullptr)
        delete cl;
}

void change::on_changeBtn_clicked()
{
    QString oldusr = ui -> usernameEdit -> text().trimmed();
    QString newusr = ui -> newusernameEdit -> text().trimmed();
    QString oldpwd = ui -> pwdEdit -> text();
    QString newpwd = ui -> newpwdEdit -> text();
    if(oldusr.length() == 0 || oldusr.length() > 256 || newusr.length() == 0 || newusr.length() > 256) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> newusernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    if(oldusr == "Tourist" || newusr == "Tourist") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> newusernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    if(oldusr == newusr) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> newusernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    for (int i=0; i<oldusr.length(); ++i) {
        if(oldusr[i] >= 'a' && oldusr[i] <= 'z') continue;
        if(oldusr[i] >= 'A' && oldusr[i] <= 'Z') continue;
        if(oldusr[i] >= '0' && oldusr[i] <= '9') continue;
        if(newusr[i] >= 'a' && newusr[i] <= 'z') continue;
        if(newusr[i] >= 'A' && newusr[i] <= 'Z') continue;
        if(newusr[i] >= '0' && newusr[i] <= '9') continue;
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> newusernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    if(oldusr != UserName) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: You can only change your account!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> newusernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    if(oldpwd.length() > 16 || oldpwd.length() == 0) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should have length between 1 and 16!"), QMessageBox :: Yes);
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    if(newpwd.length() > 16 || newpwd.length() == 0) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should have length between 1 and 16!"), QMessageBox :: Yes);
        ui -> pwdEdit -> clear();
        ui -> newpwdEdit -> clear();
        return ;
    }
    for (int i=0; i<oldpwd.length(); ++i) {
        if(oldpwd[i] == '#') {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should not include \'#\'!"), QMessageBox :: Yes);
            ui -> pwdEdit -> clear();
            ui -> newpwdEdit -> clear();
            return ;
        }
    }
    for (int i=0; i<newpwd.length(); ++i) {
        if(newpwd[i] == '#') {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should not include \'#\'!"), QMessageBox :: Yes);
            ui -> pwdEdit -> clear();
            ui -> newpwdEdit -> clear();
            return ;
        }
    }
    QString msg = "~@ChangeRequest#" + oldusr + "#" + newusr + "#" + oldpwd + "#" + newpwd;
    cl -> sendMessage(msg);
    return ;
}

void change::on_checkBox_stateChanged(int arg1)
{
    if(arg1) {
        ui -> pwdEdit -> setEchoMode(QLineEdit :: Normal);
        ui -> newpwdEdit -> setEchoMode(QLineEdit :: Normal);
    } else {
        ui -> pwdEdit -> setEchoMode(QLineEdit :: Password);
        ui -> newpwdEdit -> setEchoMode(QLineEdit :: Password);
    }
    return ;
}

void change::receive_signal(const QString& msg) {
    if(msg == "Accept") {
        UserName = ui -> newusernameEdit -> text().trimmed();
        accept();
    } else {
        if(msg == "NoUser") {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: No such user!"), QMessageBox :: Yes);
            ui -> usernameEdit -> clear();
            ui -> newusernameEdit -> clear();
            ui -> pwdEdit -> clear();
            ui -> newpwdEdit -> clear();
        } else if(msg == "WrongPwd") {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Wrong Password!"), QMessageBox :: Yes);
            ui -> pwdEdit -> clear();
            ui -> newpwdEdit -> clear();
        } else if(msg == "UserExists") {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: Username existed!"), QMessageBox :: Yes);
            ui -> newusernameEdit -> clear();
            ui -> pwdEdit -> clear();
            ui -> newpwdEdit -> clear();
        }
    }
    return ;
}

void change::Disconnect() {
    cl -> disconnect();
}
