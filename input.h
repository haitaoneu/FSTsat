#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include "tableaucon.h"
#include <qdebug.h>
//#include <mainwindow.h>

namespace Ui {
class Input;
}

class Input : public QWidget
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = 0);
    ~Input();

private slots:
    void on_pushButton_clicked();
    void Receive();


private:
    Ui::Input *ui;
    tableaucon con;
//    MainWindow mainwin;
};

#endif // INPUT_H
