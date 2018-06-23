#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Link_clicked();
    void socket_Read_Data();

    void on_Send_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket = new QTcpSocket();
};

#endif // MAINWINDOW_H
