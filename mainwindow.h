#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "client.h"
#include "change.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    chatClient *cl;
    bool isLogin;

private slots:
    void on_send_button_clicked();
    void on_actionConnect_To_Server_triggered();
    void on_actionChange_Account_triggered();
    void on_actionBlack_List_triggered();
    void on_actionExit_triggered();
    void add_new_msg(const QByteArray&);
    void on_info_text_textChanged();
    void on_pic_button_clicked();
};

#endif // MAINWINDOW_H
