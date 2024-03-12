#include "../Header_files/mainwindow.h"
#include "../Header_files/cashregisterwindow.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //QTimer timer;

    //timer.singleShot(100, &w, SLOT(hide()));

    return a.exec();
}
