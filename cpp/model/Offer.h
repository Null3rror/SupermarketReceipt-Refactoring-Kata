#ifndef CPP_OFFER_H
#define CPP_OFFER_H


#include "Product.h"
#include "iostream"
#include "SpecialOfferType.h"

class Offer {
public:
    Offer() = default;
    Offer(const SpecialOfferType& offerType, const Product& product, double argument);

    SpecialOfferType getOfferType() const;

    Product getProduct() const;

    double getArgument() const;

    virtual double calculateDiscountAmount(double unitPrice, double quantity) const;

    std::string getDiscountDescription() const;


protected:
    double argument;
    int discountThreshold;
    std::string discountDescription;
    SpecialOfferType offerType;
    Product product;

};

class XForYOffer : public Offer {
public:
    XForYOffer(const SpecialOfferType& offerType, const Product& product, double argument);
    virtual double calculateDiscountAmount(double unitPrice, double quantity) const override;
private:
    int X;
    int Y;
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
private:
    double amount;
};


#endif //CPP_OFFER_H
