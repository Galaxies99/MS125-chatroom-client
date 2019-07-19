#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();
    void Disconnect();

private slots:
    void on_regBtn_clicked();
    void receive_signal(const QString&);
    void on_backBtn_clicked();
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::regist *ui;
    chatClient *cl;
};

#endif // REGIST_H
