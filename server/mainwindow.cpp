#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server->listen(QHostAddress::Any, 8888);
    connect(server,&QTcpServer::newConnection,this,&MainWindow::server_New_Connect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::server_New_Connect()
{
    QTcpSocket *socket = server->nextPendingConnection();
    clientList.push_back(socket);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    send_Msg(QString("Enter"),socket->peerAddress().toString());
}


void MainWindow::socket_Read_Data()
{
    QByteArray buffer;
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    QString ipAddress = socket->peerAddress().toString();
    buffer = socket->readAll();
    send_Msg(QString(buffer),socket->peerAddress().toString());
}

void MainWindow::send_Msg(QString rawData,QString ipAddress)
{
    QString current_date = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd");
    QString data = QString(current_date + "   " + ipAddress + "   " + rawData);
    for(QTcpSocket *socket : clientList)
    {
        socket->write(data.toStdString().c_str());
    }
    ui->textEdit->append(data);
}
