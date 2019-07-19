#ifndef CHANGE_H
#define CHANGE_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class change;
}

class change : public QDialog
{
    Q_OBJECT

public:
    explicit change(QWidget *parent = nullptr);
    ~change();
    void Disconnect();

private slots:
    void on_changeBtn_clicked();
    void receive_signal(const QString&);
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::change *ui;
    chatClient *cl;
};

#endif // CHANGE_H
