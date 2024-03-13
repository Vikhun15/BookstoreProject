#include "database.h"
#include <QtSql>
#include <QFileInfo>
#include <QFile>


DataBase::DataBase() {
    QString path = "settings.db";
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLiteConnection");
    db.setDatabaseName(path);

    CreateTable();

    //QSqlQuery query;

    //query.exec("insert into settings(id, page) values (1, 'manage');");



}

void DataBase::CreateTable(){
    db.open();
    QString cmd = "create table if not exists settings "
                  "(id integer primary key, "
                  "page varchar(20));";
    QSqlQuery query(cmd, db);
    query.exec();
    db.close();
}

QString DataBase::GetSetting(){
    db.open();

    QString cmd = "SELECT page FROM settings;";

    QSqlQuery query(cmd, db);
    query.exec();
    query.next();
    QString txt = query.value(0).toString();
    db.close();
    return txt;
}

void DataBase::SetSetting(QString value){
    db.open();
    QString cmd = "UPDATE settings SET page='"+value+"' WHERE id=1;";
    QSqlQuery query(cmd, db);
    query.exec();
    db.close();
}

DataBase::~DataBase(){
    db.close();
}
