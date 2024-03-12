#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include "../Header_files/book.h"

namespace Ui {
class AddWindow;
}

class AddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWindow(QList<int> list,QWidget *parent = nullptr);
    Ui::AddWindow *ui;
    ~AddWindow();
public:
    QList<Book*> books;
signals:
    void closed();
private:
    QList<int> ids;
    int FindId();
    int rowNum;
    int selectedRowNum;
    int lastId;
    bool synced;
    bool CheckData();
    void closeEvent(QCloseEvent * event);
    void ReadCSV(QString path);
private slots:
    void selectedChanged();
    void AddRow();
    void RemoveRow();
    void Cancel();
    void SyncData();
    void ImportCSV();
};

#endif // ADDWINDOW_H
