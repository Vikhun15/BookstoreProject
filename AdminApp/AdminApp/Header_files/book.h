#ifndef BOOK_H
#define BOOK_H
#include <QString>

class Book
{
public:
    int id;
    QString title;
    QString category;
    double rating;
    double price;
    bool inStock;
    int quantity;
    Book();
    Book(int id, QString title, QString category, double rating, double price, bool stock, int quantity);
};

#endif // BOOK_H
