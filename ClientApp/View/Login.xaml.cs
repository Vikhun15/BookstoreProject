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
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        public Login(MainWindow owner)
        {
            this.Owner = owner;
            InitializeComponent();
            LoginViewModel vm = new LoginViewModel(this);

            usernameTxt.TextChanged += (s, e) => vm.RemovePhTxt(usernameTxt, usernamePh);
            passwordTxt.PasswordChanged += (s, e) => vm.RemovePhTxt(passwordTxt, passwordPh);

            usernameTxt.LostFocus += (s, e) => vm.CheckUsername();

            loginBtn.Click += (s, e) =>
            {
                if (vm.CheckUser(usernameTxt.Text, passwordTxt.Password))
                {
                    vm.Checkboxes();
                    MessageBox.Show(this, "Successfull login!");
                    ((MainWindow)this.Owner).Login(usernameTxt.Text);
                    this.Close();
                }
                else
                {
                    MessageBox.Show(this, "Invalid username or password!", "Invalid login", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            };

            registerBtn.Click += (s, e) =>
            {
                this.Close();
                ((MainWindow)this.Owner).OpenRegister();
            };
        }

    }
}
