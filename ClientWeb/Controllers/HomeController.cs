using ClientWeb.Models;
using Microsoft.AspNetCore.Mvc;

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
            Database db = new();
            db.TakeBook(id);
            return LocalRedirect("/Webshop");
        }
    }
}
