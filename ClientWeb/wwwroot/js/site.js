// Please see documentation at https://learn.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

document.getElementById("themeImg").addEventListener("click", function () {
    if (document.getElementById("themeImg").classList.contains("day")) {
        document.getElementById("themeImg").setAttribute("src", "/images/icons/moon.png")
        document.getElementById("themeImg").classList.remove("day")
        document.getElementById("themeImg").classList.add("night")
    }
    else{
        document.getElementById("themeImg").setAttribute("src", "/images/icons/sun.png")
        document.getElementById("themeImg").classList.remove("night")
        document.getElementById("themeImg").classList.add("day")
    }
})