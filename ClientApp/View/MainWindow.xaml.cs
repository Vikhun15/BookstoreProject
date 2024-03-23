using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using ClientApp.Model;
using ClientApp.View;
using ClientApp.ViewModel;

namespace ClientApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public ObservableCollection<Book> books = new ObservableCollection<Book>();
        public ObservableCollection<Book> cart = new ObservableCollection<Book>();
        MainWindowViewModel vm;
        public Cart cartWindow;
        public bool loggedIn = false;

        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = this;
            booksGrid.ItemsSource = books;
            vm = new MainWindowViewModel(this);
            price.Text = books.Select(x => x.price).Max().ToString();
            logoutBtn.Click += (s, e) => Logout();
            loginBtn.Click += (s, e) => OpenLogin();
            addToCartBtn.IsEnabled = false;

        }

        public void Merge(ObservableCollection<Book> input)
        {
            foreach(Book book in input)
            {
                foreach(Book book1 in books)
                {
                    if(book.id == book1.id)
                    {
                        book1.quantity += book.quantity;
                    }
                }
            }
            cartCount.Content = "0";
            booksGrid.Items.Refresh();
        }

        public void OpenLogin()
        {
            Login login = new Login(this);
            login.ShowDialog();
        }

        public void OpenRegister()
        {
            vm.OpenRegister();
        }

        public void Login(string username)
        {
            loggedIn = true;
            usernameTxt.Content = username;
            buttons1Stck.Visibility = Visibility.Collapsed;
            buttons2Stck.Visibility = Visibility.Visible;
        }
        public void Logout()
        {
            loggedIn = false;
            usernameTxt.Content = "";
            buttons2Stck.Visibility = Visibility.Collapsed;
            buttons1Stck.Visibility = Visibility.Visible;
        }
    }
}
