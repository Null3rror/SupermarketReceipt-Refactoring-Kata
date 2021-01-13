#include "OfferRepository.h"

OfferRepository& OfferRepository::getInstance() {
    static OfferRepository instance;
    return instance;
}


bool OfferRepository::isOfferForProduct(const Product& product) const {
    return offers.find(product) != offers.end();
}

const Offer& OfferRepository::getOfferForProduct(const Product& product) const {
    if (!isOfferForProduct(product)) {
        throw std::runtime_error(std::string("No offer is available for this product!\nproduct name: ") + product.getName());
    }
    auto offer = offers.find(product);
    return offer->second;
}



void OfferRepository::addOffer(const Offer&& offer) {
    offers[offer.getProduct()] = offer;
}

