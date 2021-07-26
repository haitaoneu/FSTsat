#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <time.h>
#include "input.h"
#include "random.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendOpen();

private slots:

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Input in;
    Random ran;
};

#endif // MAINWINDOW_H
