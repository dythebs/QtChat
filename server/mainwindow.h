#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void send_Msg(QString rawData, QString ipAddress);

private slots:
    void server_New_Connect();
    void socket_Read_Data();

private:
    Ui::MainWindow *ui;
    QTcpServer *server = new QTcpServer();
    QVector<QTcpSocket*> clientList;
};

#endif // MAINWINDOW_H
