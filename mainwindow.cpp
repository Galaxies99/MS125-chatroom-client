#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "change.h"

extern bool isTourist;
extern QString UserName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cl = new chatClient(this);

    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(add_new_msg(const QString&)));
    connect(this, SIGNAL(newMessageSent(const QString &)), this, SLOT(add_new_msg(const QString &)));

    setWindowTitle(tr("ChatRoom"));
    setWindowIcon(QIcon(":/Chat.ico"));

    cl -> connectToServer("127.0.0.1", 6666);
}

//destroy
MainWindow::~MainWindow()
{
    if(isTourist == 0) cl -> sendMessage("<" + UserName + "> log out.");
    delete ui;
    if(cl != nullptr)
        delete cl;
}


//send button clicked
void MainWindow::on_send_button_clicked(){
    QString toSend = ui->input_text->toPlainText();
    cl->sendMessage(UserName + ": " + toSend);
    ui->input_text->clear();
    ui->input_text->setFocus();
    QString msgTmp = "You: " + toSend;
    emit newMessageSent(msgTmp); //what's this?
}

//connect to server, ip and port is hard coded, you may add a input box
//to connect to the ip you want
void MainWindow::on_actionConnect_To_Server_triggered(){
    cl -> connectToServer("127.0.0.1", 6666);
    if(isTourist == 0) cl -> sendMessage("<" + UserName + "> log in.");
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    QString old = ui->info_text->toPlainText();
    old += (newMsg + "\n");
    ui->info_text->setText(old);
    ui->info_text->setFocus();
}

void MainWindow::on_actionExit_triggered() {
    close();
}

void MainWindow::on_actionChange_Account_triggered() {
    if(isTourist == false) {
        change ch;
        ch.exec();
        ch.Disconnect();
    }
}

