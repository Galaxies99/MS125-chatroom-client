#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <QDialog>
#include "client.h"

namespace Ui {
class blacklist;
}

class blacklist : public QDialog
{
    Q_OBJECT

public:
    explicit blacklist(QWidget *parent = nullptr);
    ~blacklist();

private slots:
    void on_addBtn_clicked();
    void receive_signal(const QString &);

    void on_removeBtn_clicked();

private:
    Ui::blacklist *ui;
    chatClient *cl;
};

#endif // BLACKLIST_H
