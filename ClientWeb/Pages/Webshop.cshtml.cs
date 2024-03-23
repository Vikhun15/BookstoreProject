using ClientWeb.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace ClientWeb.Pages
{
    public class WebshopModel : PageModel
    {
        public List<Book> books { get; set; }
        private Database db { get; set; }
        private Page page { get; set; }

        public WebshopModel()
        {
            this.page = page;
            db = new Database();
            books = db.GetBooks();
        }
    }
}
