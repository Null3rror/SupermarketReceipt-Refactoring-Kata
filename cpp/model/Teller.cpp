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



void Teller::handleOffers(Receipt& receipt, SupermarketCatalog* catalog, const ShoppingCart& cart) {
    for (const auto& productQuantity : cart.getProductQuantities()) {
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

void Teller::addProductToReceipt(const ProductQuantity& productQuantity, Receipt& receipt) const {
    Product p = productQuantity.getProduct();
    double quantity = productQuantity.getQuantity();
    double unitPrice = catalog->getUnitPrice(p);
    double price = quantity * unitPrice;
    receipt.addProduct(p, quantity, unitPrice, price);
}



Receipt Teller::checksOutArticlesFrom(ShoppingCart theCart) {
    Receipt receipt{};
    std::vector<ProductQuantity> productQuantities = theCart.getItems();
    for (const auto& pq: productQuantities) {
        addProductToReceipt(pq, receipt);
    }
    handleOffers(receipt, catalog, theCart);

    return receipt;
}

