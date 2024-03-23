using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

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
    }
}
