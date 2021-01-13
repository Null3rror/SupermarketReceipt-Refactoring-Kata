#include "Offer.h"
#include <utility>

Offer::Offer(const SpecialOfferType& offerType, Product  product, double argument)
        : offerType(offerType), product(std::move(product)), argument(argument) {}

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
    if (quantity < discountThreshold)
        return 0;

    int quantityAsInt = (int)quantity;
    int numberOfDiscounts = quantityAsInt / discountThreshold;

    double actualTotalPrice = quantity * unitPrice;
    double priceOfDiscountedItems = numberOfDiscounts * (numberOfItemsToPayWithDiscount * discountedUnitPrice);
    double remainingPriceToPay = quantityAsInt % discountThreshold * unitPrice;
    double totalPriceToPayWithDiscount = priceOfDiscountedItems + remainingPriceToPay;
    double discountAmount = actualTotalPrice - totalPriceToPayWithDiscount;

    return discountAmount;
}

std::string Offer::getDiscountDescription() const {
    return discountDescription;
}

XForYOffer::XForYOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument) {
    discountedUnitPrice = argument;
    numberOfItemsToPayWithDiscount = 1;
    if (offerType == SpecialOfferType::ThreeForTwo) {
        discountThreshold = 3;
        numberOfItemsToPayWithDiscount = 2;
    }
    discountDescription = std::to_string(discountThreshold) + " for " + std::to_string(numberOfItemsToPayWithDiscount);
}

AmountOffer::AmountOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument) {
    discountedUnitPrice = argument;
    numberOfItemsToPayWithDiscount = 1;
    if (offerType == SpecialOfferType::TwoForAmount) {
        discountThreshold = 2;
    } else if (offerType == SpecialOfferType::FiveForAmount) {
        discountThreshold = 5;
    }
    discountDescription = std::to_string(discountThreshold) + " for " + std::to_string(discountedUnitPrice);
}

PercentageOffer::PercentageOffer(const SpecialOfferType &offerType, const Product &product, double argument) : Offer(offerType, product, argument), percentage(argument) {
    discountDescription = std::to_string(percentage) + "% off";
}

double PercentageOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    double actualTotalPrice = quantity * unitPrice;
    double discountAmount = actualTotalPrice * percentage / 100.0;
    return discountAmount;
}

double AmountOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    return Offer::calculateDiscountAmount(unitPrice, quantity);
}

double XForYOffer::calculateDiscountAmount(double unitPrice, double quantity) const {
    return Offer::calculateDiscountAmount(unitPrice, quantity);
}

