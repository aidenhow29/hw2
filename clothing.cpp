#include "util.h"
#include "clothing.h"
#include "product.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size):
Product(category, name, price, qty),
brand_(brand),
size_(size) {

}

Clothing::~Clothing() {}


std::set<std::string> Clothing:: keywords() const {
    
    std::set<std::string> returnSet;
    returnSet = parseStringToWords(brand_);
    std::set<std::string> tempSet;
    tempSet = parseStringToWords(name_);
    tempSet.insert(size_);

    return returnSet;

}

std::string Clothing:: displayString() const {

    std::string returnString = name_ + " " + std::to_string(price_) + " " + std::to_string(qty_) + " " + category_ + " " + brand_ + " " + size_ + " ";
     
}

void Clothing:: dump(std::ostream& os) const{
    os << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << std::to_string(qty_) << "\n" << category_ << "\n" << brand_ << "\n" << size_ << "\n";
}


