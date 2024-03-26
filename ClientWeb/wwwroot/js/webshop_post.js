document.getElementById("price-input").addEventListener("change", function () {
  document.getElementById("price-slider-input").value =
    document.getElementById("price-input").value;
});

document
  .getElementById("price-slider-input")
  .addEventListener("change", function () {
    document.getElementById("price-input").value =
      document.getElementById("price-slider-input").value;
  });

document
  .getElementById("price-slider-input")
  .addEventListener("change", function () {
    ReloadTable(data);
  });
document.getElementById("price-input").addEventListener("change", function () {
  ReloadTable(data);
});
document.getElementById("in-stock").addEventListener("change", function () {
  ReloadTable(data);
});

for (var item of document.getElementsByClassName("category-checkboxes")) {
  item.addEventListener("change", function () {
    ReloadTable(data);
  });
}

document.getElementById("buy").addEventListener("click", function () {
  for (var item of data) {
    if (selected.includes(item.id)) {
      cart.push(item);
    }
  }
  selected = [];
  selects = document.getElementsByClassName("selected");
  while (selects.length > 0) {
    selects[0].classList.remove("selected");
  }
});

document.getElementById("cart").addEventListener("click", function () {
  document.getElementById("cart-table").innerHTML = "";
  for (var item of cart) {
    var id = "id-" + item.id;
    var elem = document.createElement("tr");
    elem.id = id;
    var title = document.createElement("td");
    title.innerText = item.title;
    elem.appendChild(title);
    var price = document.createElement("td");
    price.innerText = item.price + "$";
    elem.appendChild(price);
    var button = document.createElement("td");
    button.innerText = "-";
    button.classList.add("remove-btn");
    button.addEventListener("click", function () {
      for (var i in cart) {
        if (cart[i].id == this.parentNode.id.split("-")[1]) {
          cart.splice(i, 1);
          break;
        }
      }
      var row = this.parentNode;
      row.parentNode.removeChild(row);
    });
    elem.appendChild(button);
    document.getElementById("cart-table").appendChild(elem);
  }
  $("#cart-modal").modal();
});
