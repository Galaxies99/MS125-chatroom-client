#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QThread>

class chatClient : public QObject
{
    friend class login;
    Q_OBJECT

public:
    explicit chatClient(QObject *parent = nullptr);
    ~chatClient();

private:
    QTcpSocket *sock = nullptr;

signals:
    void newMessageRead(const QString&);
public slots:
    void readMsg();
public:
    void connectToServer(QString ip, uint16_t port);
    void sendMessage(QString msg);
};

#endif // CLIENT_H
