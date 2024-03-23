


document.getElementById("price-input").addEventListener("change", function () {
    document.getElementById("price-slider-input").value = document.getElementById("price-input").value;
})

document.getElementById("price-slider-input").addEventListener("change", function () {
    document.getElementById("price-input").value = document.getElementById("price-slider-input").value;
})