using ClientApp.ViewModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

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
            Owner = owner;
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
                    _ = MessageBox.Show(this, "Successfull registration!");
                    ((MainWindow)Owner).Login(usernameTxt.Text);
                    Close();
                }
            };

            cancelBtn.Click += (s, e) =>
            {
                Close();
            };
        }

        private void RemovePhTxt(TextBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            placeholder.Foreground = original.Text.Length > 0 ? Brushes.Transparent : (Brush)Brushes.Gray;
        }
        private void RemovePhTxt(PasswordBox original, Label placeholder)
        {
            original.Background = Brushes.White;
            original.Foreground = Brushes.Black;
            placeholder.Foreground = original.Password.Length > 0 ? Brushes.Transparent : (Brush)Brushes.Gray;
        }
    }
}
