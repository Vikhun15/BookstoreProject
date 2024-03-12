#ifndef CASHREGISTERWINDOW_H
#define CASHREGISTERWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "book.h"

namespace Ui {
class CashRegisterWindow;
}

class CashRegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashRegisterWindow(QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn,QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn, QString username,QWidget *parent = nullptr);
    explicit CashRegisterWindow(bool loggedIn, QString username, QList<Book*> books,QWidget *parent = nullptr);
    ~CashRegisterWindow();
    Login* login;
    bool loggedIn;
    void ChangeData(bool loggedIn, QString username, QList<Book*> books);

private:
    Ui::CashRegisterWindow *ui;
    QList<int> ids;
    QList<Book*> books;
    void SyncIds();
    void SyncTable();
    void Setup();
    QString dir;
    int selectedRowNum;
    int selectedListNum;
    void calculatePrice();
    bool checkDiscount();
    void calculateTotal();
    void closeEvent(QCloseEvent * event);
private slots:
    void changeUsername();
    void logout_click();
    void mode_click();
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
