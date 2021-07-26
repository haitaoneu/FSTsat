#ifndef TABLEAUELI_H
#define TABLEAUELI_H

#include <QWidget>
#include <string>
#include <fstream>
#include <iostream>
#include <qdebug.h>
using namespace std;

namespace Ui {
class tableaueli;
}

class tableaueli : public QWidget
{
    Q_OBJECT

public:
    explicit tableaueli(QWidget *parent = 0);
    ~tableaueli();
    void Eliminate();
    void Painter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::tableaueli *ui;
    int cont;
    ofstream truthfile;//写入真值

};

#endif // TABLEAUELI_H
