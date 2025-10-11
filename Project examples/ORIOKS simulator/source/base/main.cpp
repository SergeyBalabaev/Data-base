#define _NO_DEBUG_HEAP 1

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    MainWindow w;
    w.setWindowTitle("Orioks");
    w.show();
    return a.exec();
}
