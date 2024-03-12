#include "../Header_files/book.h"
#include <QString>

Book::Book(int id, QString title, QString category, double rating, double price, bool stock, int quantity) {
    Book::id = id;
    Book::title = title;
    Book::category = category;
    Book::rating = rating;
    Book::price = price;
    Book::inStock = stock;
    Book::quantity = quantity;
}
