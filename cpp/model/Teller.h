#ifndef CPP_TELLER_H
#define CPP_TELLER_H


#include <map>
#include "SupermarketCatalog.h"
#include "OfferRepository.h"
#include "Receipt.h"
#include "ShoppingCart.h"

class Teller {
public:
    Teller(SupermarketCatalog* catalog);

    void addSpecialOffer(SpecialOfferType offerType, const Product& product, double argument);

    Receipt checksOutArticlesFrom(ShoppingCart theCart);

    void handleOffers(Receipt& receipt, SupermarketCatalog* catalog, const ShoppingCart& cart);

    void addProductToReceipt(const ProductQuantity& productQuantity, Receipt& receipt) const;

private:
    SupermarketCatalog* catalog;
};


#endif //CPP_TELLER_H
