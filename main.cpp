#include "mainwindow.h"
#include "initializer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Initializer initializer;
    initializer.start();
    return a.exec();
}
