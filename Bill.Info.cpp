#include "Bill.Info.hpp"

string const &BillInfo::getItemName() const {
    return (this->ItemName);
}

string const &BillInfo::getItemManufacturingDate() const {
    return (this->ItemManufacturingDate);
}

double const &BillInfo::getItemPrice() const {
    return (this->ItemPrice);
}

double const &BillInfo::getItemTaxPercent() const {
    return (this->ItemTaxPercent);
}

long long const &BillInfo::getItemQuantity() const {
    return (this->ItemQuantity);
}

long long const &BillInfo::getItemNumber() const {
    return (this->ItemNumber);
}

string const &BillInfo::getItemCategory() const {
    return (this->ItemCategory);
}

double const &BillInfo::getItemDiscount() const {
    return (this->ItemDiscount);
}

void BillInfo::setItemName(string Name) {
    this->ItemName = Name;
}

void BillInfo::setItemManufacturingDate(string Data) {
    this->ItemManufacturingDate = Data;
}

void BillInfo::setItemPrice(string Price) {
    this->ItemPrice = stod(Price);
}

void BillInfo::setItemTaxPercent(string TaxPercent) {
    this->ItemTaxPercent = stod(TaxPercent);
}

void BillInfo::setItemQuantity(string Quantity) {
    this->ItemQuantity = stoll(Quantity);
}

void BillInfo::setItemNumber(string Number) {
    this->ItemNumber = stoll(Number);
}

void BillInfo::setItemCategory(string Category) {
    this->ItemCategory = Category;
}

void BillInfo::setItemDiscount(string Discount) {
    this->ItemDiscount = stod(Discount);
}
