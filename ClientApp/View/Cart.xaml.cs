using ClientApp.Model;
using ClientApp.ViewModel;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;

namespace ClientApp.View
{
    /// <summary>
    /// Interaction logic for Cart.xaml
    /// </summary>
    public partial class Cart : Window
    {
        public ObservableCollection<Book> books = new ObservableCollection<Book>();
        private readonly CartViewModel vm;
        public Cart(ObservableCollection<Book> books, MainWindow owner)
        {
            Owner = owner;
            InitializeComponent();
            this.books = books;
            booksGrid.ItemsSource = books;
            clearBtn.IsEnabled = books.Count > 0;
            finalBtn.IsEnabled = books.Count > 0;
            vm = new CartViewModel(this);

            CalculateTotal();

            clearBtn.Click += (s, e) => clear_click();
            finalBtn.Click += (s, e) => vm.Finalize(books);
        }

        private void CalculateTotal()
        {
            double sum = 0;
            foreach (Book book in books)
            {
                sum += book.quantity * book.price;
            }
            totalTxt.Content = $"Total: {sum}$";
        }

        private void clear_click()
        {
            ((MainWindow)Owner).Merge(books);
            vm.Clear();
        }

        private void Remove_Click(object sender, RoutedEventArgs e)
        {
            Book model = (sender as Button).DataContext as Book;
            if (model.quantity - 1 > 0)
            {
                model.quantity--;
            }
            else
            {
                _ = books.Remove(model);
            }
            CalculateTotal();
            booksGrid.Items.Refresh();
            ((MainWindow)Owner).Merge(new ObservableCollection<Book> { model });
            clearBtn.IsEnabled = books.Count > 0;
            finalBtn.IsEnabled = books.Count > 0;
        }
    }
}
