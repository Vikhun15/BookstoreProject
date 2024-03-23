using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Npgsql;

namespace ClientApp.Model
{
    public class Book
    {
        public int id { get; set; }
        public string title { get; set; }
        public string category { get; set; }
        public double rating { get;set; }
        public double price { get; set; }
        public bool inStock { get; set; }
        public int quantity { get; set; }

        public Book(NpgsqlDataReader reader)
        {
            id = reader.GetInt32(0);
            title = reader.GetString(1);
            category = reader.GetString(2);
            rating = reader.GetDouble(3);
            price = Math.Round(reader.GetDouble(4), 2);
            inStock = reader.GetBoolean(5);
            quantity = reader.GetInt32(6);
        }

        public Book(int id, string title, string category, double rating, double price, bool inStock, int quantity)
        {
            this.id = id;
            this.title = title;
            this.category = category;
            this.rating = rating;
            this.price = price;
            this.inStock = inStock;
            this.quantity = quantity;
        }

        public Book(Book book)
        {
            this.id = book.id;
            this.title = book.title;
            this.category = book.category;
            this.rating = book.rating;
            this.price = book.price;
            this.inStock = book.inStock;
            this.quantity = book.quantity;
        }
    }
}
