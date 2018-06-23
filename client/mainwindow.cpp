#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Link_clicked()
{
    QString ipAddress = ui->IP_Address_Edit->text();
    socket->connectToHost(ipAddress,8888);
    ui->IP_Address_Edit->setEnabled(false);
    ui->Link->setEnabled(false);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
}


void MainWindow::on_Send_clicked()
{
    QString data = ui->Edit_Zone->text();
    socket->write(data.toStdString().c_str());
    ui->Edit_Zone->setText("");
}

void MainWindow::on_Quit_clicked()
{
    socket->write("Quit");
    this->close();
}

void MainWindow::socket_Read_Data()
{
    QByteArray buffer;
    buffer = socket->readAll();
    QString data = QString(buffer);
    ui->textEdit->append(data);
}
