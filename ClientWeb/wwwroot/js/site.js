// Please see documentation at https://learn.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

document.getElementById("themeImg").addEventListener("click", function () {
    if (document.getElementById("themeImg").classList.contains("day")) {
        document.getElementById("themeImg").setAttribute("src", "/images/icons/moon.png")
        document.getElementById("themeImg").classList.remove("day")
        document.getElementById("themeImg").classList.add("night")
        document.getElementsByTagName("nav")[0].style.borderColor = "#361401"
        document.getElementsByTagName("main")[0].style.backgroundColor = "#361401"
        document.getElementsByTagName("main")[0].style.color = "white"
        document.getElementById("bg-image").style.backgroundColor = "rgba(0,0,0,0.8)"

        for (var item of document.getElementsByClassName("button")) {
            item.style.backgroundColor = "#590101"
        }
        if (document.getElementsByClassName("bookCard").length > 0) {
            for (var item of document.getElementsByClassName("bookCard")) {
                item.style.backgroundColor = "#590101"
            }
        }
        if (document.getElementsByClassName("webshop-table").length > 0) {
            for (var item of document.getElementsByClassName("webshop-table")) {
                item.style.backgroundColor = "#653719"
            }
            $("#cart-modal > .modal-dialog > .modal-content")[0].style.backgroundColor = "#653719"
            document.getElementById("buy").style.backgroundColor = "#653719"
            document.getElementById("cart").style.backgroundColor = "#653719"
        }
        setCookie("night");
    }
    else {
        document.getElementById("themeImg").setAttribute("src", "/images/icons/sun.png")
        document.getElementById("themeImg").classList.remove("night")
        document.getElementById("themeImg").classList.add("day")
        document.getElementsByTagName("nav")[0].style.borderColor = "burlywood"
        document.getElementsByTagName("main")[0].style.backgroundColor = "burlywood"
        document.getElementsByTagName("main")[0].style.color = "black"
        document.getElementById("bg-image").style.backgroundColor = "rgba(0,0,0,0.4)"
        for (var item of document.getElementsByClassName("button")) {
            item.style.backgroundColor = "saddlebrown"
        }
        if (document.getElementsByClassName("bookCard").length > 0) {
            for (var item of document.getElementsByClassName("bookCard")) {
                item.style.backgroundColor = "sandybrown"
            }
        }
        if (document.getElementsByClassName("webshop-table").length > 0) {
            for (var item of document.getElementsByClassName("webshop-table")) {
                item.style.backgroundColor = "saddlebrown"
            }
            $("#cart-modal > .modal-dialog > .modal-content")[0].style.backgroundColor = "white"
            document.getElementById("buy").style.backgroundColor = "white"
            document.getElementById("cart").style.backgroundColor = "white"
        }
        setCookie("day");

    }
})

function setCookie(value) {
    document.cookie = "theme" + "=" + value;
}
function getCookie(cname) {
    let name = cname + "=";
    let ca = document.cookie.split(';');
    for (let i = 0; i < ca.length; i++) {
        let c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return "";
}

    function SwitchTheme(theme) {
        if (theme == "night") {
            document.getElementById("themeImg").setAttribute("src", "/images/icons/moon.png")
            document.getElementById("themeImg").classList.remove("day")
            document.getElementById("themeImg").classList.add("night")
            document.getElementsByTagName("nav")[0].style.borderColor = "#361401"
            document.getElementsByTagName("main")[0].style.backgroundColor = "#361401"
            document.getElementsByTagName("main")[0].style.color = "white"
            document.getElementById("bg-image").style.backgroundColor = "rgba(0,0,0,0.8)"

            for (var item of document.getElementsByClassName("button")) {
                item.style.backgroundColor = "#590101"
            }
            if (document.getElementsByClassName("bookCard").length > 0) {
                for (var item of document.getElementsByClassName("bookCard")) {
                    item.style.backgroundColor = "#590101"
                    item.style.borderColor = "white"
                }
            }
            if (document.getElementsByClassName("webshop-table").length > 0) {
                for (var item of document.getElementsByClassName("webshop-table")) {
                    item.style.backgroundColor = "#653719"
                }
                $("#cart-modal > .modal-dialog > .modal-content")[0].style.backgroundColor = "#653719"
                document.getElementById("buy").style.backgroundColor = "#653719"
                document.getElementById("cart").style.backgroundColor = "#653719"
            }
            if (document.getElementsByClassName("post-title").length > 0) {
                for (var item of document.getElementsByClassName("post-title")) {
                    item.style.borderColor = "white"
                }
            }
            if (document.getElementsByClassName("review").length > 0) {
                for (var item of document.getElementsByClassName("review")) {
                    item.style.borderColor = "white"
                }
            }
            setCookie("night");
        }
        else {
            document.getElementById("themeImg").setAttribute("src", "/images/icons/sun.png")
            document.getElementById("themeImg").classList.remove("night")
            document.getElementById("themeImg").classList.add("day")
            document.getElementsByTagName("nav")[0].style.borderColor = "burlywood"
            document.getElementsByTagName("main")[0].style.backgroundColor = "burlywood"
            document.getElementsByTagName("main")[0].style.color = "black"
            document.getElementById("bg-image").style.backgroundColor = "rgba(0,0,0,0.4)"
            for (var item of document.getElementsByClassName("button")) {
                item.style.backgroundColor = "saddlebrown"
            }
            if (document.getElementsByClassName("bookCard").length > 0) {
                for (var item of document.getElementsByClassName("bookCard")) {
                    item.style.backgroundColor = "sandybrown"
                    item.style.borderColor = "black"
                }
            }
            if (document.getElementsByClassName("webshop-table").length > 0) {
                for (var item of document.getElementsByClassName("webshop-table")) {
                    item.style.backgroundColor = "saddlebrown"
                }
                $("#cart-modal > .modal-dialog > .modal-content")[0].style.backgroundColor = "white"
                document.getElementById("buy").style.backgroundColor = "white"
                document.getElementById("cart").style.backgroundColor = "white"
            }
            if (document.getElementsByClassName("post-title").length > 0) {
                for (var item of document.getElementsByClassName("post-title")) {
                    item.style.borderColor = "black"
                }
            }
            if (document.getElementsByClassName("review").length > 0) {
                for (var item of document.getElementsByClassName("review")) {
                    item.style.borderColor = "black"
                }
            }
            setCookie("day");

        }
    }