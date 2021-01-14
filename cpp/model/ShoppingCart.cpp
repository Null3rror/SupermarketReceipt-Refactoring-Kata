#include "ShoppingCart.h"

void addItemQuantity(const Product& product, double quantity);

std::vector<ProductQuantity> ShoppingCart::getItems() const {
    return items;
}

std::map<const Product, double> ShoppingCart::getProductQuantities() const {
    return productQuantities;
}

void ShoppingCart::addItem(const Product& product) {
    addItemQuantity(product, 1.0);
}

void ShoppingCart::addItemQuantity(const Product& product, double quantity) {
    items.emplace_back(product, quantity);
    if (productQuantities.find(product) != productQuantities.end()) {
        productQuantities[product] += quantity;
    } else {
        productQuantities[product] = quantity;
    }
}



