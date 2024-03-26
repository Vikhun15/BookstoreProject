using ClientApp.Data;
using ClientApp.Model;
using ClientApp.View;
using System.Collections.ObjectModel;
using System.Linq;

namespace ClientApp.ViewModel
{
    internal class CartViewModel
    {
        private readonly Cart cart;
        private readonly Database db;
        public CartViewModel(Cart cart)
        {
            this.cart = cart;
            db = new Database();
        }

        public void Finalize(ObservableCollection<Book> books)
        {
            db.Finalize(books.ToList());
            Clear();
        }

        public void Clear()
        {
            cart.books.Clear();
            cart.totalTxt.Content = $"Total: 0$";
            cart.clearBtn.IsEnabled = false;
            cart.finalBtn.IsEnabled = false;
        }
    }
}
