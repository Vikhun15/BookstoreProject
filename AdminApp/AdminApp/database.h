#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>

class DataBase
{
public:
    DataBase();
    ~DataBase();
    QString GetSetting();
    void SetSetting(QString value);
private:
    QSqlDatabase db;
    QString path;
    void CreateTable();
};

#endif // DATABASE_H
