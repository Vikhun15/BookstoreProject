#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Login* login;

private:
    Ui::MainWindow *ui;
private slots:
    void changeUsername();
    void logout_click();
    void mode_click();
    void add_click();
    void edit_click();
    void remove_click();
    void stock_click();
    void export_click();
    void sync_click();
};
#endif // MAINWINDOW_H
