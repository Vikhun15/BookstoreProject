using ClientApp.ViewModel;
using System.Windows;

namespace ClientApp.View
{
    /// <summary>
    /// Interaction logic for Login.xaml
    /// </summary>
    public partial class Login : Window
    {
        public Login(MainWindow owner)
        {
            Owner = owner;
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
                    _ = MessageBox.Show(this, "Successfull login!");
                    ((MainWindow)Owner).Login(usernameTxt.Text);
                    Close();
                }
                else
                {
                    _ = MessageBox.Show(this, "Invalid username or password!", "Invalid login", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            };

            registerBtn.Click += (s, e) =>
            {
                Close();
                ((MainWindow)Owner).OpenRegister();
            };
        }

    }
}
