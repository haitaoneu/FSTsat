#ifndef RANDOM_H
#define RANDOM_H

#include <QWidget>
#include "formula.h"

namespace Ui {
class Random;
}

class Random : public QWidget
{
    Q_OBJECT

public:
    explicit Random(QWidget *parent = 0);
    ~Random();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Random *ui;
    Formula fm;
};

#endif // RANDOM_H
