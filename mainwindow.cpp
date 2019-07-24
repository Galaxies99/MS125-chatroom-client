#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "change.h"
#include <QFileDialog>

extern bool isTourist;
extern QString UserName;
extern QString ipAddr;
extern int portAddr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cl = new chatClient(this);
    cl -> connectToServer(ipAddr, portAddr);

    connect(cl, SIGNAL(newMessageRead(const QString&)), this, SLOT(add_new_msg(const QString&)));
    connect(this, SIGNAL(newMessageSent(const QString &)), this, SLOT(add_new_msg(const QString &)));

    setWindowTitle(tr("ChatRoom"));
    setWindowIcon(QIcon(":/Chat.ico"));

    isLogin = 0;
}

//destroy
MainWindow::~MainWindow()
{
    if(isLogin == 1) {
        cl -> sendMessage("~@Unlog#" + UserName);
    }
    delete ui;
    if(cl != nullptr)
        delete cl;
}

void stringToHtmlFilter(QString &str) {
   str.replace("&", "&amp;");
   str.replace(">", "&gt;");
   str.replace("<", "&lt;");
   str.replace("\"", "&quot;");
   str.replace("\'", "&#39;");
   str.replace(" ", "&nbsp;");
   str.replace("\n", "<br>");
   str.replace("\r", "<br>");
}

void stringToHtml(QString &str, QString color) {
     str = QString("<span style=\" color:" + color + ";\">%2</span>").arg(str);
}


//send button clicked
void MainWindow::on_send_button_clicked(){
    if(isLogin == 0) return;
    QString toSend = ui->input_text->toPlainText();
    cl->sendMessage(UserName + "#" + toSend);
    ui->input_text->clear();
    ui->input_text->setFocus();
}

//connect to server, ip and port is hard coded, you may add a input box
//to connect to the ip you want
void MainWindow::on_actionConnect_To_Server_triggered(){
    cl -> connectToServer("127.0.0.1", 6666);
    if(isLogin == 0) {
        cl -> sendMessage("~@Login#" + UserName);
        isLogin = 1;
    }
}

QString dealText(QString msg) {
    int pos = 0;
    for (; pos < msg.length(); ++pos)
        if (msg[pos] == '#') break;
    if (pos == msg.length()) {
        stringToHtmlFilter(msg);
        stringToHtml(msg, "#FF6347");
        return msg;
    }
    QString part1 = msg.left(pos) + ":\n", part2 = msg.mid(pos + 1);
    stringToHtmlFilter(part1);
    stringToHtmlFilter(part2);
    stringToHtml(part1, "#1E90FF");
    return part1 + part2;
}

//show message on textbrowser
void MainWindow::add_new_msg(const QString &newMsg){
    if(newMsg.length() >= 2 && newMsg[0] == '~' && newMsg[1] == '@') {
        QString msg = newMsg.mid(2);
        int i = 0;
        for (; i < msg.length(); ++i) if(msg[i] == '#') break;
        ui -> level_label -> setText(msg.left(i));
        if(i == msg.length()) return ;
        QString toPrint = dealText(msg.mid(i + 1) + "\n");
        ui->info_text->insertHtml(toPrint);
        ui->info_text->setFocus();
        return ;
    }
    QString toPrint = dealText(newMsg + "\n");
    ui->info_text->insertHtml(toPrint);
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

void MainWindow::on_info_text_textChanged()
{
    ui->info_text->moveCursor(QTextCursor::End);
}
