#ifndef FORMULA_H
#define FORMULA_H

#include <QWidget>
#include "tableaucon.h"

namespace Ui {
class Formula;
}

class Formula : public QWidget
{
    Q_OBJECT


public:
    explicit Formula(QWidget *parent = 0);
    ~Formula();

    void GenerateSign(QString &str);
    void Generatef(QString &str);
    void GenerateFormula(QString &str);
    void GenerateCase(int i);
    void Transform(QString &str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Formula *ui;
        QString str;
        tableaucon tc;

};

#endif // FORMULA_H
