#ifndef CPP_SHOPPINGCART_H
#define CPP_SHOPPINGCART_H


#include <vector>
#include <map>
#include "ProductQuantity.h"
#include "OfferRepository.h"
#include "Receipt.h"
#include "SupermarketCatalog.h"
#include <algorithm> // for std::copy_if

class ShoppingCart {
public:
    std::vector<ProductQuantity> getItems() const;

    std::map<const Product, double> getProductQuantities() const;

    void addItem(const Product& product);

    void addItemQuantity(const Product& product, double quantity);

    void handleOffers(Receipt& receipt, SupermarketCatalog* catalog);

private:
    std::vector<ProductQuantity> items;
    std::map<const Product, double> productQuantities;
};


#endif //CPP_SHOPPINGCART_H
