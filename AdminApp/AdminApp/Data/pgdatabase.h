#ifndef PGDATABASE_H
#define PGDATABASE_H
#include <QSqlDatabase>
#include "../Header_files/book.h"
#include "../Header_files/user.h"

class PGDatabase
{
public:
    PGDatabase();
    QSqlDatabase db;
    QList<Book*> GetBooks();
    void RecreateBooks();
    void FillBooks(QList<Book*> books);
    QList<User*> GetUsers();
    ~PGDatabase();
};

#endif // PGDATABASE_H
