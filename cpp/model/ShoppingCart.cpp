#include "ShoppingCart.h"

void addItemQuantity(const Product& product, double quantity);

std::vector<ProductQuantity> ShoppingCart::getItems() const {
    return items;
}

std::map<Product, double> ShoppingCart::getProductQuantities() const {
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


void ShoppingCart::handleOffers(Receipt& receipt, SupermarketCatalog* catalog) {
    for (const auto& productQuantity : productQuantities) {
        Product product = productQuantity.first;
        double quantity = productQuantity.second;
        if (OfferRepository::getInstance().isOfferForProduct(product)) {
            auto offer = OfferRepository::getInstance().getOfferForProduct(product);
            double unitPrice = catalog->getUnitPrice(product);
            double discountAmount = offer->calculateDiscountAmount(unitPrice, quantity);
            Discount* discount = new Discount(offer->getDiscountDescription(), -discountAmount, product); // TODO: memory leak??

            if (discountAmount != 0)
                receipt.addDiscount(*discount);
        }
    }
}
