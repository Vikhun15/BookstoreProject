using ClientApp.Data;
using ClientApp.Model;
using ClientApp.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ClientApp.ViewModel
{
    internal class MainWindowViewModel
    {
        private readonly MainWindow window;
        private readonly Database db;
        public List<Book> books;

        public MainWindowViewModel(MainWindow window)
        {
            this.window = window;
            db = new Database();

            books = db.GetBooks();
            GetBooks(window.books);

            foreach (string category in books.Select(x => x.category).Distinct().OrderBy(x => x).ToList())
            {
                CheckBox box = new CheckBox
                {
                    IsChecked = true,
                    Content = category
                };
                box.Checked += (s, e) => Refresh();
                box.Unchecked += (s, e) => Refresh();
                _ = window.categoryList.Items.Add(box);
            }
            window.priceSlider.Maximum = books.Select(x => x.price).Max();
            window.priceSlider.Value = books.Select(x => x.price).Max();
            window.priceSlider.Minimum = books.Select(x => x.price).Min();
            window.price.TextChanged += (s, e) => PriceChanged();

            window.cartBtn.Click += (s, e) =>
            {
                window.cartWindow = new Cart(window.cart, window);
                _ = window.cartWindow.ShowDialog();
            };
            window.finalizeBtn.Click += (s, e) =>
            {
                if (window.loggedIn)
                {
                    window.cartWindow = new Cart(window.cart, window);
                    _ = window.cartWindow.ShowDialog();
                }
                else
                {
                    _ = MessageBox.Show(window, "You have to log in to finalize the purchase!");
                    window.OpenLogin();
                }
            };

            window.minTxt.Content = books.Select(x => x.price).Min().ToString() + "$";
            window.maxTxt.Content = books.Select(x => x.price).Max().ToString() + "$";

            window.priceSlider.ValueChanged += (s, e) => PriceRangeChanged(s, e);
            window.stockRad.Click += (s, e) => Refresh();
            window.storageRad.Click += (s, e) => Refresh();
            window.searchbar.TextChanged += (s, e) => SearchBarChanged();

            window.booksGrid.SelectionChanged += (s, e) =>
            {
                window.addToCartBtn.IsEnabled = window.booksGrid.SelectedItems.Count > 0;
            };
            window.addToCartBtn.Click += (s, e) => AddToCart();
            window.registerBtn.Click += (s, e) =>
            {
                OpenRegister();
            };

            CheckLoggedIn();
        }

        public void OpenRegister()
        {
            Register reg = new Register(window);
            _ = reg.ShowDialog();
        }

        private void CheckLoggedIn()
        {
            LocalDatabase localdb = new LocalDatabase();
            string result = localdb.SavedUser();
            if (result != "")
            {
                window.Login(result);
            }
        }
        private void PriceChanged()
        {
            bool correct = double.TryParse(window.price.Text, out double result);
            if ((correct && result <= window.priceSlider.Maximum && result >= window.priceSlider.Minimum) || window.price.Text.Length == 0)
            {
                if (window.price.Text.Length > 0)
                {
                    window.priceSlider.Value = result;
                }
                window.price.Foreground = Brushes.Black;
                window.price.Background = Brushes.White;
                Refresh();
            }
            else
            {
                window.price.Foreground = Brushes.White;
                window.price.Background = Brushes.Red;
            }
        }

        private void PriceRangeChanged(object sender, EventArgs e)
        {
            window.price.Text = Math.Round(window.priceSlider.Value, 2).ToString();
            Refresh();
        }

        private void SearchBarChanged()
        {
            window.searchbarPh.Content = window.searchbar.Text.Length != 0 ? "" : (object)"Search";
            Refresh();
        }

        private void Refresh()
        {
            window.books.Clear();

            foreach (Book book in books)
            {
                bool toAdd = true;
                string sb = window.searchbar.Text;
                if ((book.title.Contains(sb) || book.category.Contains(sb)) &&
                    (book.price < window.priceSlider.Value))
                {
                    toAdd = toAdd && true;
                }
                else
                {
                    toAdd = toAdd && false;
                    continue;
                }
                if (window.stockRad.IsChecked == true)
                {
                    if (book.inStock)
                    {
                        toAdd = toAdd == true && true;
                    }
                    else
                    {
                        continue;
                    }
                }
                if (window.storageRad.IsChecked == true)
                {
                    if (book.quantity > 0)
                    {
                        toAdd = toAdd == true && true;
                    }
                    else
                    {
                        continue;
                    }
                }
                foreach (CheckBox sender in window.categoryList.Items)
                {
                    if (sender.Content.ToString() == book.category)
                    {
                        toAdd = toAdd && sender.IsChecked == true;
                    }
                }
                if (toAdd)
                {
                    window.books.Add(book);
                }
            }
        }

        private void AddToCart()
        {
            if (window.booksGrid.SelectedItems.Count > 0)
            {
                foreach (Book book in window.booksGrid.SelectedItems)
                {
                    if (book.quantity > 0)
                    {
                        book.quantity--;
                        window.booksGrid.Items.Refresh();
                        if (window.cart.Where(x => x.id == book.id).Count() > 0)
                        {
                            Book nBook = window.cart.Where(x => x.id == book.id).First();
                            nBook.quantity++;
                        }
                        else
                        {
                            Book nBook = new Book(book)
                            {
                                quantity = 1
                            };
                            window.cart.Add(nBook);
                            window.cartCount.Content = Convert.ToInt32(window.cartCount.Content) + 1;
                        }
                    }
                }
            }
        }

        public void GetBooks(ObservableCollection<Book> retBooks)
        {
            foreach (Book book in books)
            {
                retBooks.Add(book);
            }
        }
    }
}
