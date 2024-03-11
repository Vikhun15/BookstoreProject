#include "../Header_files/mainwindow.h"
#include "../Header_files/login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
