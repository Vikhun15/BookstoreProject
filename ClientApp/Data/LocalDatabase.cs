using System.Data.SQLite;
using System.Windows;

namespace ClientApp.Data
{
    internal class LocalDatabase
    {
        private readonly string filename;
        private readonly SQLiteConnection connection;

        public LocalDatabase()
        {
            filename = "settings.db";
            connection = new SQLiteConnection($"Data Source={filename}; Version = 3; New = True; Compress = True; ");

            try
            {
                connection.Open();
                Begin();
            }
            catch (SQLiteException)
            {
                _ = MessageBox.Show("Could save settings!");
            }
        }

        private void Begin()
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection)
            {
                CommandText = $"CREATE TABLE IF NOT EXISTS users(signedIn bool, username varchar(255), password varchar(255));"
            };
            _ = cmd.ExecuteNonQuery();
        }

        public string SavedUser()
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection)
            {
                CommandText = "SELECT signedIn, username FROM users;"
            };

            SQLiteDataReader reader = cmd.ExecuteReader();
            string result = "";
            while (reader.Read())
            {
                if (reader.GetBoolean(0))
                {
                    result = reader.GetString(1);
                    break;
                }
            }


            reader.Close();
            return result;
        }

        public string SavedPassword(string username)
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection)
            {
                CommandText = $"SELECT password FROM users WHERE username = '{username}';"
            };

            SQLiteDataReader reader = cmd.ExecuteReader();
            _ = reader.Read();

            string result = reader.GetString(0);

            reader.Close();

            return result;
        }

        public void RememberPassword(string username, string password)
        {
            if (CheckContains(username))
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection)
                {
                    CommandText = $"UPDATE users SET password='{password}' WHERE username = '{username}';"
                };
                _ = cmd.ExecuteNonQuery();
            }
            else
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection)
                {
                    CommandText = $"INSERT INTO users(signedIn, username, password) VALUES (false, '{username}', '{password}');"
                };
                _ = cmd.ExecuteNonQuery();
            }
        }

        public void RememberLogin(string username, string password)
        {
            if (CheckContains(username))
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection)
                {
                    CommandText = $"UPDATE users SET signedIn=false;"
                };
                _ = cmd.ExecuteNonQuery();
                cmd.CommandText = $"UPDATE users SET signedIn=true WHERE username = '{username}';";
                _ = cmd.ExecuteNonQuery();
            }
            else
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection)
                {
                    CommandText = $"UPDATE users SET signedIn=false;"
                };
                _ = cmd.ExecuteNonQuery();
                cmd.CommandText = $"INSERT INTO users(signedIn, username, password) VALUES (true, '{username}', '{password}');";
                _ = cmd.ExecuteNonQuery();
            }
        }

        public bool CheckContains(string username)
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection)
            {
                CommandText = $"SELECT username FROM users WHERE username = '{username}';"
            };

            int count = 0;
            SQLiteDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                count++;
            }

            reader.Close();

            return count > 0;

        }

    }
}
