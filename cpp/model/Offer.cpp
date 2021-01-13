#include "Offer.h"

Offer::Offer(const SpecialOfferType& offerType, const Product& product, double argument)
        : offerType(offerType), product(product), argument(argument) {}

SpecialOfferType Offer::getOfferType() const {
        return offerType;
}

Product Offer::getProduct() const {
        return product;
}

double Offer::getArgument() const {
        return argument;
}

double Offer::calculateDiscountAmount(double unitPrice, double quantity) const {
    std::cout << "base" << std::endl;
    if (quantity < discountThreshold) return 0;
    int quantityAsInt = (int)quantity;
    int numberOfDiscounts = quantityAsInt / discountThreshold;
    double discountAmount = quantity * unitPrice - ((numberOfDiscounts * 2 * unitPrice) + quantityAsInt % discountThreshold * unitPrice);
    return discountAmount;
}

std::string Offer::getDiscountDescription() const {
    return discountDescription;
}

XForYOffer::XForYOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument) {
    X = 1;
    Y = 1;
    if (offerType == SpecialOfferType::ThreeForTwo) {
        X = 3;
        Y = 2;
    }
    discountThreshold = X;
    discountDescription = std::to_string(discountThreshold) + " for " + std::to_string(Y); // TODO: refactor this since it's kinda duplicate code.
}

AmountOffer::AmountOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument), amount(argument) {
    discountThreshold = 1;
    if (offerType == SpecialOfferType::TwoForAmount) {
        discountThreshold = 2;
    } else if (offerType == SpecialOfferType::FiveForAmount) {
        discountThreshold = 5;
    }
    discountDescription = std::to_string(discountThreshold) + " for " + std::to_string(amount);
}

PercentageOffer::PercentageOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument), percentage(argument) {
    discountDescription = std::to_string(percentage) + "% off";
}

double PercentageOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    double discountAmount = quantity * unitPrice * percentage / 100.0;
    std::cout << "test" << std::endl;
    return discountAmount;
}

double AmountOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    if (quantity < discountThreshold) return 0;
    int quantityAsInt = (int)quantity;
    int numberOfDiscounts = quantityAsInt / discountThreshold;
    double discountAmount = quantity * unitPrice - ((numberOfDiscounts * amount) + quantityAsInt % discountThreshold * unitPrice);
    return discountAmount;
}

double XForYOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    if (quantity < discountThreshold) return 0;
    int quantityAsInt = (int)quantity;
    int numberOfDiscounts = quantityAsInt / discountThreshold;
    double discountAmount = quantity * unitPrice - ((numberOfDiscounts * Y * unitPrice) + quantityAsInt % discountThreshold * unitPrice);
    return discountAmount;
}

