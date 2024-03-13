#ifndef CASHREGISTERWINDOW_H
#define CASHREGISTERWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "book.h"
#include "../Data/pgdatabase.h"
#include "../database.h"

namespace Ui {
class CashRegisterWindow;
}

class CashRegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashRegisterWindow(DataBase* db, PGDatabase* pgdb, QList<Book*> books ,QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn,DataBase* db, PGDatabase* pgdb, QList<Book*> books ,QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn, QString username,QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn, QString username, QList<Book*> books,QWidget *parent = nullptr);
    ~CashRegisterWindow();
    Login* login;
    bool loggedIn;
    PGDatabase *pgdb;
    DataBase *db;
    QList<Book*> books;
    void ChangeData(bool loggedIn, QString username, QList<Book*> books);

private:
    Ui::CashRegisterWindow *ui;
    QList<int> ids;
    void SyncIds();
    void SyncTable();
    void Setup();
    QString dir;
    int selectedRowNum;
    QList<int> selectedRows;
    QList<int> selectedItems;
    int selectedListNum;
    void calculatePrice();
    bool checkDiscount();
    void calculateTotal();
    void closeEvent(QCloseEvent * event);

signals:
    void mode_clicked();
public slots:
    void mode_click();
    void refresh_table();
private slots:
    void changeUsername();
    void logout_click();
    void selectedChanged();
    void sync_click();
    void searchChanged();
    void add_click();
    void remove_click();
    void list_click();
    void table_click();
    void change_discount();
};

#endif // CASHREGISTERWINDOW_H
