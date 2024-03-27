using ClientApp.Model;
using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

namespace ClientApp.Data
{
    internal class Database
    {
        private static string connectionString;
        private static NpgsqlConnection connection;

        public Database()
        {
            connectionString = "Host=surus.db.elephantsql.com;Port=5432;Database=iyqfkyce;User Id=iyqfkyce;Password=6VMoIXqvz4Ht3vkPeSPl9UgjqKHrz25y";
            try
            {
                connection = new NpgsqlConnection(connectionString);
                connection.Open();
            }
            catch (NpgsqlException)
            {
                _ = MessageBox.Show("ERROR: Couldn't connect to database!", "Error!", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }

        public List<Book> GetBooks()
        {
            List<Book> books = new List<Book>();

            string command = "SELECT id, title, category, rating, price, stock, quantity FROM books;";
            NpgsqlCommand cmd = new NpgsqlCommand(command, connection);

            NpgsqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                books.Add(new Book(reader));
            }
            reader.Close();

            return books;
        }

        public void Finalize(List<Book> books)
        {

            NpgsqlCommand cmd = new NpgsqlCommand
            {
                Connection = connection
            };

            foreach (Book book in books)
            {
                cmd.CommandText = $"UPDATE books SET quantity={book.quantity} WHERE id={book.id};";
                _ = cmd.ExecuteNonQuery();
            }

        }

        public bool CheckUser(string username, string password)
        {
            if (connection.State == System.Data.ConnectionState.Closed)
            {
                connection.Open();
            }
            List<User> users = new List<User>();

            string txt = "SELECT id, username, email, password FROM clients " +
                        $"WHERE username = '{username}' AND password = '{password}';";
            NpgsqlCommand cmd = new NpgsqlCommand(txt, connection);
            NpgsqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                users.Add(new User(reader));
            }

            reader.Close();

            return users.Count() > 0;
        }

        public bool CheckUsername(string username)
        {
            List<User> users = new List<User>();

            string txt = $"SELECT id, username, email, password FROM clients WHERE username = '{username}';";
            NpgsqlCommand cmd = new NpgsqlCommand(txt, connection);
            NpgsqlDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                users.Add(new User(reader));
            }
            reader.Close();


            return users.Count() > 0;
        }

        public void RegisterUser(string username, string email, string password)
        {
            int lastId = 0;
            List<User> users = new List<User>();

            NpgsqlCommand start = new NpgsqlCommand("", connection)
            {
                CommandText = "SELECT id, username, email, password FROM clients;"
            };

            NpgsqlDataReader reader = start.ExecuteReader();
            while (reader.Read())
            {
                users.Add(new User(reader));
            }

            reader.Close();


            while (users.Select(x => x.GetId()).Contains(lastId))
            {
                lastId++;
            }
            string txt = $"INSERT INTO clients(id, username, email, password) " +
                              $"VALUES ({lastId}, '{username}', '{email}', '{password}');";
            NpgsqlCommand cmd = new NpgsqlCommand(txt, connection);
            _ = cmd.ExecuteNonQuery();
        }

        public void Dispose()
        {
            connection.Close();
        }

        ~Database()
        {
            connection.Close();
        }

    }
}
