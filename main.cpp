//#include "mainwindow.h"
#include "input.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    Input in;
    in.show();
//    w.show();

    return a.exec();
}
