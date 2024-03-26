using Npgsql;

namespace ClientWeb.Models
{
    public class Database
    {
        private string connectionString;
        private NpgsqlConnection connection;

        public Database()
        {
            connectionString = "Host=surus.db.elephantsql.com;Port=5432;Database=iyqfkyce;User Id=iyqfkyce;Password=6VMoIXqvz4Ht3vkPeSPl9UgjqKHrz25y";
            connection = new NpgsqlConnection(connectionString);
        }

        public List<Book> GetBooks()
        {
            connection.Open();
            List<Book> books = new List<Book>();

            string txt = "SELECT id, title, category, rating, price, stock, quantity FROM books;";

            NpgsqlCommand cmd = new NpgsqlCommand(txt, connection);

            var reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                books.Add(new Book(reader));
            }

            connection.Close();
            return books;
        }

        public void TakeBook(int id)
        {
            int quantity = 0;
            connection.Open();

            string txt = $"SELECT id, title, category, rating, price, stock, quantity FROM books WHERE id = {id};";

            NpgsqlCommand cmd = new NpgsqlCommand(txt, connection);

            var reader = cmd.ExecuteReader();

            reader.Read();
            quantity = reader.GetInt32(6);

            reader.Close();

            txt = $"UPDATE books SET quantity = {quantity - 1} WHERE id = {id}";
            cmd.CommandText = txt;
            cmd.ExecuteNonQuery();

            connection.Close();
        }
    }
}
