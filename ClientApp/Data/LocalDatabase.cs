using System.Data.SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Data.Entity;

namespace ClientApp.Data
{
    internal class LocalDatabase
    {
        private string filename;
        private SQLiteConnection connection;

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
                MessageBox.Show("Could save settings!");
            }
        }

        private void Begin()
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection);
            cmd.CommandText = $"CREATE TABLE IF NOT EXISTS users(signedIn bool, username varchar(255), password varchar(255));";
            cmd.ExecuteNonQuery();
        }

        public string SavedUser()
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection);
            cmd.CommandText = "SELECT signedIn, username FROM users;";

            var reader = cmd.ExecuteReader();
            string result = "";
            while(reader.Read())
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
            SQLiteCommand cmd = new SQLiteCommand("", connection);
            cmd.CommandText = $"SELECT password FROM users WHERE username = '{username}';";

            var reader = cmd.ExecuteReader();
            reader.Read();

            string result = reader.GetString(0);

            reader.Close();

            return result;
        }

        public void RememberPassword(string username, string password)
        {
            if (CheckContains(username))
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection);
                cmd.CommandText = $"UPDATE users SET password='{password}' WHERE username = '{username}';";
                cmd.ExecuteNonQuery();
            }
            else
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection);
                cmd.CommandText = $"INSERT INTO users(signedIn, username, password) VALUES (false, '{username}', '{password}');";
                cmd.ExecuteNonQuery();
            }
        }

        public void RememberLogin(string username, string password)
        {
            if (CheckContains(username))
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection);
                cmd.CommandText = $"UPDATE users SET signedIn=false;";
                cmd.ExecuteNonQuery();
                cmd.CommandText = $"UPDATE users SET signedIn=true WHERE username = '{username}';";
                cmd.ExecuteNonQuery();
            }
            else
            {
                SQLiteCommand cmd = new SQLiteCommand("", connection);
                cmd.CommandText = $"UPDATE users SET signedIn=false;";
                cmd.ExecuteNonQuery();
                cmd.CommandText = $"INSERT INTO users(signedIn, username, password) VALUES (true, '{username}', '{password}');";
                cmd.ExecuteNonQuery();
            }
        }

        public bool CheckContains(string username)
        {
            SQLiteCommand cmd = new SQLiteCommand("", connection);
            cmd.CommandText = $"SELECT username FROM users WHERE username = '{username}';";

            int count = 0;
            var reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                count++;
            }

            reader.Close();

            return count > 0;

        }

    }
}
