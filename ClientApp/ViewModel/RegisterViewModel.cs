using ClientApp.Data;
using ClientApp.View;
using System;
using System.Net.Mail;
using System.Windows.Controls;
using System.Windows.Media;

namespace ClientApp.ViewModel
{
    internal class RegisterViewModel
    {
        private readonly Register reg;
        private readonly Database db = new Database();
        public RegisterViewModel(Register reg)
        {
            this.reg = reg;
        }

        public bool CheckData()
        {
            bool email = CheckEmail(reg.emailTxt.Text);
            bool user = CheckUsername(reg.usernameTxt.Text);
            bool pass = CheckPasswordAgain(reg.passwordTxt.Password, reg.passwordAgainTxt.Password);
            CheckBg(email, reg.emailTxt);
            CheckBg(user, reg.usernameTxt);
            CheckBg(pass, reg.passwordAgainTxt);

            return email && user && pass;
        }

        public void AddUser()
        {
            db.RegisterUser(reg.usernameTxt.Text, reg.emailTxt.Text, reg.passwordTxt.Password);
        }

        private bool CheckEmail(string txt)
        {
            try
            {
                MailAddress m = new MailAddress(txt);
                return true;
            }
            catch (FormatException)
            {
                return false;
            }
        }

        private bool CheckUsername(string username)
        {
            return !db.CheckUsername(username);
        }

        private bool CheckPasswordAgain(string original, string again)
        {
            return original == again;
        }

        private void CheckBg(bool value, Control cont)
        {
            if (value)
            {
                cont.Background = Brushes.White;
                cont.Foreground = Brushes.Black;
            }
            else
            {
                cont.Background = Brushes.Red;
                cont.Foreground = Brushes.White;
            }
        }

    }
}
