using ClientWeb.Models;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace ClientWeb.Pages
{
    public class WebshopModel : PageModel
    {
        public List<Book> books { get; set; }
        private Database db { get; set; }

        public WebshopModel()
        {
            db = new Database();
            books = db.GetBooks();
        }

        public void ReloadBooks()
        {
            books = db.GetBooks();
        }
    }
}
