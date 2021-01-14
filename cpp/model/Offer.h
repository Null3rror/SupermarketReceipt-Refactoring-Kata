#ifndef CPP_OFFER_H
#define CPP_OFFER_H


#include "Product.h"
#include "map"
#include "vector"
#include "SpecialOfferType.h"

class Offer {

public:
    Offer() = default;
    Offer(const SpecialOfferType& offerType, Product  product, double argument);

    SpecialOfferType getOfferType() const;

    Product getProduct() const;

    double getArgument() const;

    virtual bool canUseDiscount(double quantity) const;
    virtual double calculateDiscountAmount(double unitPrice, double quantity) const = 0;

    std::string getDiscountDescription() const;

protected:
    double argument;
    double discountedUnitPrice;
    int discountThreshold;
    int numberOfItemsToPayWithDiscount;
    std::string discountDescription;
    SpecialOfferType offerType;
    Product product;


};

class XForYOffer : public Offer {
public:
    XForYOffer(const SpecialOfferType& offerType, const Product& product, double argument);
    virtual double calculateDiscountAmount(double unitPrice, double quantity) const override;
};

class PercentageOffer : public Offer {
public:
    PercentageOffer(const SpecialOfferType& offerType, const Product& product, double argument);
    virtual double calculateDiscountAmount(double unitPrice, double quantity) const override;
private:
    double percentage;
};

class AmountOffer : public Offer {
public:
    AmountOffer(const SpecialOfferType& offerType, const Product& product, double argument);
    virtual double calculateDiscountAmount(double unitPrice, double quantity) const override;
};

class BundleOffer {
public:
    BundleOffer(const SpecialOfferType& offerType, const std::map<const Product, double>& productsArguments);
private:
    std::vector<PercentageOffer> offers;
};


#endif //CPP_OFFER_H
