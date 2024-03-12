#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "addwindow.h"

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
    AddWindow* addWindow;

private:
    Ui::MainWindow *ui;
    QList<int> ids;
    QList<Book*> books;
    void SyncIds();
    void SyncTable();
    void WriteCSV(std::string path);
    QString dir;
    int selectedRowNum;
private slots:
    void changeUsername();
    void logout_click();
    void mode_click();
    void add_click();
    void edit_click();
    void remove_click();
    void selectedChanged();
    void stock_click();
    void export_click();
    void sync_click();
    void add_to_table();
    void searchChanged();
};
#endif // MAINWINDOW_H
