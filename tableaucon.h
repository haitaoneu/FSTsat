#ifndef TABLEAUCON_H
#define TABLEAUCON_H

#include <QWidget>
#include <qdebug.h>


#include "tableaueli.h"



namespace Ui {
class tableaucon;
}

class tableaucon : public QWidget
{
    Q_OBJECT

public:
    explicit tableaucon(QWidget *parent = 0);
    ~tableaucon();
    void setFormula(QString);
    void ConTab();
    void Alpha();
    void Print();



private slots:
    void on_pushButton_clicked();

private:
    Ui::tableaucon *ui;
    QString f;
    int flag;
    int cont;
    ofstream confile;
    ifstream readfile;//读取公式
    tableaueli te;
    void Painter();
};

#endif // TABLEAUCON_H
