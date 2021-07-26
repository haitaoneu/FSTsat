#include "input.h"
#include "ui_input.h"

Input::Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
//    connect(&mainwin,SIGNAL(sendOpen()),this,SLOT(Receive()));
}

Input::~Input()
{
    delete ui;
}

void Input::on_pushButton_clicked()
{
    QString str=ui->lineEdit->text();
    qDebug()<<str;

    con.setFormula(str);
    con.ConTab();
    con.show();
    this->close();

}

void Input::Receive()
{
    this->show();
}
