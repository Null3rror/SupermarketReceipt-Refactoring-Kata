#include "Teller.h"

Teller::Teller(SupermarketCatalog *catalog) : catalog(catalog) {}

void Teller::addSpecialOffer(SpecialOfferType offerType, const Product& product, double argument) {
    Offer* offer = nullptr;
    if (offerType == SpecialOfferType::TwoForAmount || offerType == SpecialOfferType::FiveForAmount) {
        offer = new AmountOffer(offerType, product, argument);
    } else if (offerType == SpecialOfferType::ThreeForTwo) {
        offer = new XForYOffer(offerType, product, argument);
    } else if (offerType == SpecialOfferType::TenPercentDiscount) {
        offer = new PercentageOffer(offerType, product, argument);
    }
    OfferRepository::getInstance().addOffer(offer);
}

Receipt Teller::checksOutArticlesFrom(ShoppingCart theCart) {
    Receipt receipt{};
    std::vector<ProductQuantity> productQuantities = theCart.getItems();
    for (const auto& pq: productQuantities) {
        Product p = pq.getProduct();
        double quantity = pq.getQuantity();
        double unitPrice = catalog->getUnitPrice(p);
        double price = quantity * unitPrice;
        receipt.addProduct(p, quantity, unitPrice, price);
    }
    theCart.handleOffers(receipt, catalog);

    return receipt;
}
