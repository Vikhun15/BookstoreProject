using ClientApp.Data;
using ClientApp.View;
using System.Windows.Controls;
using System.Windows.Media;

namespace ClientApp.ViewModel
{
    internal class LoginViewModel
    {
        private readonly Login login;
        private Database db;
        private readonly LocalDatabase localdb;

        public LoginViewModel(Login login)
        {
            this.login = login;
            localdb = new LocalDatabase();
        }

        public bool CheckUser(string username, string password)
        {
            db = new Database();

            bool result = db.CheckUser(username, password);

            db.Dispose();

            return result;
        }

        public void CheckUsername()
        {
            if (localdb.CheckContains(login.usernameTxt.Text))
            {
                login.passwordTxt.Password = localdb.SavedPassword(login.usernameTxt.Text);
            }
        }

        public void Checkboxes()
        {
            if (login.loggedInCheck.IsChecked == true)
            {
                localdb.RememberLogin(login.usernameTxt.Text, login.passwordTxt.Password);
            }
            if (login.rememberCheck.IsChecked == true)
            {
                localdb.RememberPassword(login.usernameTxt.Text, login.passwordTxt.Password);
            }
        }


        public void RemovePhTxt(TextBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            placeholder.Foreground = original.Text.Length > 0 ? Brushes.Transparent : (Brush)Brushes.Gray;
        }
        public void RemovePhTxt(PasswordBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            placeholder.Foreground = original.Password.Length > 0 ? Brushes.Transparent : (Brush)Brushes.Gray;
        }

    }
}
