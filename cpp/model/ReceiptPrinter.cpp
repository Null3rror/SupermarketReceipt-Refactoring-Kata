#include "ReceiptPrinter.h"



std::string ReceiptPrinter::printReceipt(const Receipt &receipt) const {
    std::string result;
    for (const auto &item : receipt.getItems()) {
        result.append(presentReceiptItem(item));
    }
    for (const auto &discount : receipt.getDiscounts()) {
        result.append(presentDiscount(discount));
    }
    result.append("\n");
    result.append(presentTotal(receipt));
    return result;
}

std::string ReceiptPrinter::presentReceiptItem(const ReceiptItem &item) const {
    std::string price = getFormattedNumberAsString(item.getTotalPrice(), 2);
    std::string name = item.getProduct().getName();

    std::string line = formatLineWithWhitespace(name, price);

    if (item.getQuantity() != 1) {
        line += "  " + getFormattedNumberAsString(item.getPrice(), 2) + " * " + presentQuantity(item) + "\n";
    }
    return line;
}

std::string ReceiptPrinter::presentDiscount(const Discount &discount) const {
    std::string name = discount.getDescription() + "(" + discount.getProduct().getName() + ")";
    std::string pricePresentation = getFormattedNumberAsString(discount.getDiscountAmount(), 2);
    return formatLineWithWhitespace(name, pricePresentation);
}

std::string ReceiptPrinter::presentTotal(const Receipt &receipt) const {
    std::string total = "Total: ";
    std::string pricePresentation = presentPrice(receipt.getTotalPrice());
    return formatLineWithWhitespace(total, pricePresentation);
}

std::string ReceiptPrinter::formatLineWithWhitespace(const std::string &name, const std::string &value) const {
    int whitespaceSize = columns - name.length() - value.length();
    std::string whitespace;
    for (int i = 0; i < whitespaceSize; i++) {
        whitespace.append(" ");
    }
    return name + whitespace + value + "\n";
}

std::string ReceiptPrinter::presentPrice(double price) const {
    return getFormattedNumberAsString(price, 2);
}

std::string ReceiptPrinter::presentQuantity(const ReceiptItem &item) {
    return ProductUnit::Each == item.getProduct().getUnit()
           ? getFormattedNumberAsString(item.getQuantity(), 0)
           : getFormattedNumberAsString(item.getQuantity(), 3);
}

std::string ReceiptPrinter::getFormattedNumberAsString(double number, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    return stream.str();
}