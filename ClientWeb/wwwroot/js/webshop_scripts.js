
function CheckData() {
    var priceMax = document.getElementById("price-slider-input").value;
    var inStock = document.getElementById("in-stock").checked

    var categories = []
    for (var item of document.getElementById("categories").children) {
        if (item.tagName == "INPUT") {
            if (!item.checked) {
                categories.push(item.value);
            }
        }
    }

    return [priceMax, inStock, categories]
}

function ReloadTable(list) {
    document.getElementById("webshop-table").innerHTML = "";
    var ret = CheckData()
    var priceMax = ret[0]
    var inStock = ret[1]
    var categories = ret[2]
    for (var item of list) {
        if (priceMax < item.price || categories.includes(item.category) || (inStock && !item.inStock) ){
            continue;
        }
        
            var elem = document.createElement("tr")
            var title = document.createElement("td")
            title.innerText = item.title;
            var category = document.createElement("td")
            category.innerText = item.category;
            var rating = document.createElement("td")
            var ratingValue = item.rating;
        
            var count = 0;
        for (var i = 0; i < Math.round(ratingValue); i++)
        {
            count++;
            var img = document.createElement("img")
            img.classList.add("webshop-star")
            img.src = "/images/icons/filled_star.png"
            rating.appendChild(img)
        }
        if (count < 5) {
            while (count < 5) {
                var img = document.createElement("img")
                img.classList.add("webshop-star")
                img.src = "/images/icons/unfilled_star.png"
                rating.appendChild(img)
                count++;
            }
        }
            var price = document.createElement("td")
            price.innerText = item.price + "$";
            elem.appendChild(title)
            elem.appendChild(category)
            elem.appendChild(rating)
        elem.appendChild(price)
        elem.value = item.id;
        elem.addEventListener("click", function () {
            ChangeSelected(this)
        })
            document.getElementById("webshop-table").appendChild(elem)
    }
}

function ChangeSelected(item) {
    if (item.classList.contains("selected")) {
        for (var select of selected) {
            if (select == item.value) {
                selected.pop(select)
                break;
            }
        }
    }
    else {
        selected.push(item.value)
    }
    item.classList.toggle("selected")
    
}


