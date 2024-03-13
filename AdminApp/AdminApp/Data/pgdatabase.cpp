#include "pgdatabase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QDebug>
#include <algorithm>
#include <QSqlError>
#include "../Header_files/book.h"
#include "../Header_files/user.h"

PGDatabase::PGDatabase() {
    db = QSqlDatabase::addDatabase("QPSQL", "PostgreSQLConnection");
    db.setHostName("surus.db.elephantsql.com");

    db.setDatabaseName("iyqfkyce");
    db.setUserName("iyqfkyce");
    db.setPassword("6VMoIXqvz4Ht3vkPeSPl9UgjqKHrz25y");

    db.setPort(5432);
    db.open();

}

QList<Book*> PGDatabase::GetBooks(){
    QList<Book*> books;


    QString cmd = "SELECT id, title, category, rating, price, stock, quantity from books;";
    QSqlQuery *query = new QSqlQuery(db);
    query->exec(cmd);
    while(query->next()){
        int id = query->value("id").toInt();
        QString title = query->value("title").toString();
        QString category = query->value("category").toString();
        double rating = query->value("rating").toDouble();
        double price = query->value("price").toDouble();
        bool inStock = query->value("stock").toBool();
        int quantity = query->value("quantity").toInt();
        books.append(new Book(id, title, category,rating, price, inStock, quantity));
    }

    return books;
}

//TODO: user checking
QList<User*> PGDatabase::GetUsers(){
    QList<User*> users;


    QString cmd = "SELECT id, username, password from users;";
    QSqlQuery *query = new QSqlQuery(db);
    query->exec(cmd);
    while(query->next()){
        int id = query->value("id").toInt();
        QString username = query->value("username").toString();
        QString password = query->value("password").toString();
        users.append(new User(id, username, password));
    }

    return users;
}

void PGDatabase::FillBooks(QList<Book *> books){
    RecreateBooks();
    QSqlQuery *query = new QSqlQuery(db);
    QString cmd = "";
    for(int i = 0; i < books.length(); i++){
        QString stock = (books[i]->inStock? "true" : "false");
        QString title = books[i]->title;
        title.replace('\'', '`');
        cmd += QString("INSERT INTO books(id, title, category, rating, price, stock, quantity) VALUES (")+ QString::number(books[i]->id) + ", '" + title + "','"+ books[i]->category + "', " + QString::number(books[i]->rating) + "," + QString::number(books[i]->price) + ", " +  stock + ","+ QString::number(books[i]->quantity) + ");";
    }
    if(!cmd.isEmpty()){
        query->exec(cmd);
    }
    delete query;
}

void PGDatabase::RecreateBooks(){

    QString cmd = "DROP TABLE books;";
    QSqlQuery *query = new QSqlQuery(db);
    query->exec(cmd);

    cmd = "CREATE TABLE books(id INT PRIMARY KEY,title varchar(255),category varchar(255),rating real,price real,stock bool,quantity int);";
    query->exec(cmd);
}

PGDatabase::~PGDatabase(){
    db.close();
}
