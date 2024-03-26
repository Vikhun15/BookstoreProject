using Npgsql;

namespace ClientApp.Model
{
    internal class User
    {
        private int id { get; }
        private string username { get; }
        private string email { get; }
        private string password { get; }

        public User(NpgsqlDataReader reader)
        {
            id = reader.GetInt32(0);
            username = reader.GetString(1);
            email = reader.GetString(2);
            password = reader.GetString(3);
        }

        public User(int id, string username, string email, string password)
        {
            this.id = id;
            this.username = username;
            this.email = email;
            this.password = password;
        }

        public bool CheckUser(string username, string password)
        {
            return (this.username == username || email == username) && this.password == password;
        }

        public bool CheckUsername(string username)
        {
            return this.username == username;
        }

        public bool CheckEmail(string email)
        {
            return this.email == email;
        }

        public string GetUsername()
        {
            return username;
        }

        public int GetId()
        {
            return id;
        }

    }
}
