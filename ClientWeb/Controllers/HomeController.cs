using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using ClientWeb.Models;

namespace ClientWeb.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return LocalRedirect("/Index");
        }

        public IActionResult Blog()
        {
            return LocalRedirect("/Blog");
        }

        public IActionResult Webshop()
        {
            return LocalRedirect("/Webshop");
        }

        public IActionResult About()
        {
            return LocalRedirect("/About");
        }

        [Route("/BuyBook")]
        public IActionResult BuyBook(int id)
        {
            Database db = new Database();
            db.TakeBook(id);
            return LocalRedirect("/Webshop");
        }
    }
}
