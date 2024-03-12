#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>
#include "book.h"

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditWindow(Book* book, QList<int> id,QWidget *parent = nullptr);
    ~EditWindow();
    Book* book;
    QList<int> ids;


private:
    Ui::EditWindow *ui;
    bool CheckData();
    void accept();
};

#endif // EDITWINDOW_H
