#ifndef SUPERMARKET_OFFERREPOSITORY_H
#define SUPERMARKET_OFFERREPOSITORY_H

#include "Offer.h"
#include <map>
#include <stdexcept>
#include <iostream>
class OfferRepository {

public:

    OfferRepository(OfferRepository& other) = delete;
    OfferRepository(OfferRepository&&) = delete;
    void operator=(const OfferRepository&) = delete;

    static OfferRepository& getInstance();

    bool isOfferForProduct(const Product& product) const;
    const Offer* getOfferForProduct(const Product& product) const;
    void addOffer(Offer* offer);

protected:
    OfferRepository() = default;


private:
    std::map<Product, Offer*> offers;

};

#endif //SUPERMARKET_OFFERREPOSITORY_H

