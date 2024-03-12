#include "database.h"
#include <QtSql>
#include <QFileInfo>
#include <QFile>


DataBase::DataBase() {
    QString path = "settings.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    printf(db.lastError().text().toLocal8Bit().data());

    CreateTable();

    //QSqlQuery query;

    //query.exec("insert into settings(id, page) values (1, 'manage');");



}

void DataBase::CreateTable(){
    QSqlQuery query;
    query.exec("create table if not exists settings "
               "(id integer primary key, "
               "page varchar(20));");
}

QString DataBase::GetSetting(){
    QSqlQuery query;
    query.exec("SELECT page FROM settings;");
    query.next();
    QString txt = query.value(0).toString();
    return txt;
}

void DataBase::SetSetting(QString value){
    QSqlQuery query;
    query.exec("UPDATE settings SET page='"+value+"' WHERE id=1;");
}

DataBase::~DataBase(){
    db.close();
}
