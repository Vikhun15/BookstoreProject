using ClientApp.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace ClientApp.View
{
    /// <summary>
    /// Interaction logic for Register.xaml
    /// </summary>
    public partial class Register : Window
    {
        public Register(MainWindow owner)
        {
            InitializeComponent();
            this.Owner = owner;
            usernameTxt.TextChanged += (s, e) => RemovePhTxt(usernameTxt, usernamePh);
            emailTxt.TextChanged += (s, e) => RemovePhTxt(emailTxt, emailPh);
            passwordTxt.PasswordChanged += (s, e) => RemovePhTxt(passwordTxt, passwordPh);
            passwordAgainTxt.PasswordChanged += (s, e) => RemovePhTxt(passwordAgainTxt, passwordAgainPh);
            RegisterViewModel reg = new RegisterViewModel(this);


            registerBtn.Click += (s, e) =>
            {
                if (reg.CheckData())
                {
                    reg.AddUser();
                    MessageBox.Show(this, "Successfull registration!");
                    ((MainWindow)this.Owner).Login(usernameTxt.Text);
                    this.Close();
                }
            };

            cancelBtn.Click += (s, e) =>
            {
                this.Close();
            };
        }

        private void RemovePhTxt(TextBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            if (original.Text.Length > 0)
            {
                placeholder.Foreground = Brushes.Transparent;
            }
            else
            {
                placeholder.Foreground = Brushes.Gray;
            }
        }
        private void RemovePhTxt(PasswordBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            if (original.Password.Length > 0)
            {
                placeholder.Foreground = Brushes.Transparent;
            }
            else
            {
                placeholder.Foreground = Brushes.Gray;
            }
        }
    }
}
