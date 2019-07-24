#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "change.h"
#include <QFileDialog>
#include "blacklist.h"

extern bool isTourist;
extern QString UserName;
extern QString ipAddr;
extern int portAddr;
extern int picID;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cl = new chatClient(this);
    cl -> connectToServer(ipAddr, portAddr);

    connect(cl, SIGNAL(newMessageReadByte(const QByteArray&)), this, SLOT(add_new_msg(const QByteArray&)));

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

void stringToHtmlFilter(QByteArray &str) {
   str.replace("&", "&amp;");
   str.replace(">", "&gt;");
   str.replace("<", "&lt;");
   str.replace("\"", "&quot;");
   str.replace("\'", "&#39;");
   str.replace(" ", "&nbsp;");
   str.replace("\n", "<br>");
   str.replace("\r", "<br>");
}

void stringToHtml(QByteArray &str, QByteArray color) {
     str = "<span style=\" color:" + color + ";\">" + str + "</span>";
}

void imgPathToHtml(QByteArray &path) {
     path = "<img src=\"" + path +"\"/>";
}


//send button clicked
void MainWindow::on_send_button_clicked(){
    if(isLogin == 0) return;
    QString toSend = ui->input_text->toPlainText();
    cl->sendMessage(UserName + "#." + toSend);
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

QByteArray dealText(QByteArray msg) {
    int pos = 0;
    for (; pos < msg.length(); ++pos)
        if (msg[pos] == '#') break;
    if (pos == msg.length()) {
        stringToHtmlFilter(msg);
        stringToHtml(msg, "#FF6347");
        return msg;
    }
    if(msg[pos + 1] == '.') {
        QByteArray part1 = msg.left(pos) + ":\n", part2 = msg.mid(pos + 2);
        stringToHtmlFilter(part1);
        stringToHtmlFilter(part2);
        stringToHtml(part1, "#1E90FF");
        return part1 + part2;
    }
    if(msg[pos + 1] == '#') {
        // jpg
        QByteArray part1 = msg.left(pos) + ":\n", pics = msg.mid(pos + 2), part2 = "\n";
        stringToHtmlFilter(part1);
        stringToHtmlFilter(part2);
        stringToHtml(part1, "#1E90FF");
        QString pp = QDir::currentPath() + "\\";
        QByteArray path = pp.toUtf8() + "pic" + QByteArray :: number(picID) + ".jpg";
        ++picID;
        QFile pic(path);
        pic.open(QIODevice::ReadWrite);
        pic.write(pics);
        pic.close();
        imgPathToHtml(path);
        return part1 + path + part2;
    }
    if(msg[pos + 1] == '#') {
        // png
        QByteArray part1 = msg.left(pos) + ":\n", pics = msg.mid(pos + 2), part2 = "\n";
        stringToHtmlFilter(part1);
        stringToHtmlFilter(part2);
        stringToHtml(part1, "#1E90FF");
        QString pp = QDir::currentPath() + "\\";
        QByteArray path = pp.toUtf8() + "pic" + QByteArray :: number(picID) + ".png";
        ++picID;
        QFile pic(path);
        pic.open(QIODevice::ReadWrite);
        pic.write(pics);
        pic.close();
        imgPathToHtml(path);
        return part1 + path + part2;
    }
    return "";
}

//show message on textbrowser
void MainWindow::add_new_msg(const QByteArray &Msg){
    if(Msg.length() >= 2 && Msg[0] == '~' && Msg[1] == '@') {
        QByteArray msg = Msg.mid(2);
        int i = 0;
        for (; i < msg.length(); ++i) if(msg[i] == '#') break;
        ui -> level_label -> setText(msg.left(i));
        if(i == msg.length()) return ;
        QByteArray toPrint = dealText(msg.mid(i + 1) + "\n");
        ui->info_text->insertHtml(QString::fromUtf8(toPrint));
        ui->info_text->setFocus();
        return ;
    }
    QByteArray toPrint = dealText(Msg + "\n");
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

void MainWindow::on_pic_button_clicked()
{
    if(isTourist == false) {
        QString path = QFileDialog :: getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));
        if(path.length() == 0) return;
        QFile pic(path);
        if(!pic.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, tr("Warning"), tr("Cannot open the image file."));
            return ;
        }
        QByteArray dat = pic.readAll();
        pic.close();
        if(dat.size() > 20000000) {
            QMessageBox::information(nullptr, tr("Warning"), tr("The image is too large!"));
            return ;
        }
        if(path.right(3) == "jpg") dat.prepend("##");
        if(path.right(3) == "png") dat.prepend("#$");
        dat.prepend(UserName.toUtf8());
        cl -> sendMessage(dat);
    }
    return ;
}

void MainWindow::on_actionBlack_List_triggered() {
    if(isTourist == false) {
        blacklist w;
        w.exec();
        return ;
    }
}
