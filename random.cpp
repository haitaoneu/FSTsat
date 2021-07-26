#include "random.h"
#include "ui_random.h"

Random::Random(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Random)
{
    ui->setupUi(this);
}

Random::~Random()
{
    delete ui;
}

void Random::on_pushButton_clicked()
{
    int num=ui->lineEdit->text().toInt();
    fm.GenerateCase(num);
    fm.show();
    this->close();
}
