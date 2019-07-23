#include "regist.h"
#include "ui_regist.h"

extern bool isTourist;
extern QString UserName;

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);

    cl = new chatClient(this);
    cl -> connectToServer("127.0.0.1", 6666);

    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(receive_signal(const QString&)));

    setWindowTitle(tr("Register"));
    setWindowIcon(QIcon(":/Chat.ico"));
}

regist::~regist()
{
    delete ui;
    if(cl != nullptr) delete cl;
}

void regist::receive_signal(const QString& msg) {
    if(msg == "Accept") accept();
    else {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username: Username existed!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
    }
    return ;
}

void regist::on_regBtn_clicked()
{
    QString username = ui -> usernameEdit -> text().trimmed();
    QString pwd = ui -> pwdEdit -> text();
    QString pwd2 = ui -> pwd2Edit -> text();
    if(username.length() < 3 || username.length() > 256) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
        return ;
    }
    if(username == "Tourist") {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
        return ;
    }
    for (int i=0; i<username.length(); ++i) {
        if(username[i] >= 'a' && username[i] <= 'z') continue;
        if(username[i] >= 'A' && username[i] <= 'Z') continue;
        if(username[i] >= '0' && username[i] <= '9') continue;
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid username!"), QMessageBox :: Yes);
        ui -> usernameEdit -> clear();
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
        return ;
    }
    UserName = username;
    if(pwd.length() > 16 || pwd.length() == 0) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should have length between 1 and 16!"), QMessageBox :: Yes);
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
        return ;
    }
    if(pwd != pwd2) {
        QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password does not match!"), QMessageBox :: Yes);
        ui -> pwdEdit -> clear();
        ui -> pwd2Edit -> clear();
        return ;
    }
    for (int i=0; i<pwd.length(); ++i) {
        if(pwd[i] == '#') {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should not include \'#\'!"), QMessageBox :: Yes);
            ui -> pwdEdit -> clear();
            ui -> pwd2Edit -> clear();
            return ;
        }
    }
    for (int i=0; i<pwd2.length(); ++i) {
        if(pwd2[i] == '#') {
            QMessageBox :: warning(this, tr("Warning"), tr("Invalid password: Password should not include \'#\'!"), QMessageBox :: Yes);
            ui -> pwdEdit -> clear();
            ui -> pwd2Edit -> clear();
            return ;
        }
    }
    QString msg = "~@RegisterRequest#" + username + "#" + pwd;
    cl -> sendMessage(msg);
    return ;
}

void regist::on_backBtn_clicked()
{
    accept();
    return ;
}

void regist::Disconnect() {
    cl -> disconnect();
}

void regist::on_checkBox_stateChanged(int arg1)
{
    if(arg1) {
        ui -> pwdEdit -> setEchoMode(QLineEdit :: Normal);
        ui -> pwd2Edit -> setEchoMode(QLineEdit :: Normal);
    } else {
        ui -> pwdEdit -> setEchoMode(QLineEdit :: Password);
        ui -> pwd2Edit -> setEchoMode(QLineEdit :: Password);
    }
    return ;
}
