#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "regist.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void Disconnect();

private slots:
    void on_loginBtn_clicked();
    void receive_signal(const QString&);

    void on_registerBtn_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::login *ui;
    chatClient *cl;
};

#endif // LOGIN_H
