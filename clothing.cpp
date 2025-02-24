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
    tempSet.insert(convToLower(size_));
    
    std::set<std::string>:: iterator it;
    for(it = tempSet.begin(); it != tempSet.end(); it++){
      returnSet.insert(*it);
    }

    return returnSet;

}

std::string Clothing:: displayString() const {
    std::stringstream ss("");
    ss << std::fixed << std:: setprecision(2) << price_;
    std::string returnString = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ + "\n" + ss.str() + " " + std::to_string(qty_) + " left.";

    return returnString;
}

void Clothing:: dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << std::to_string(qty_) << "\n" << size_ << "\n" << brand_ << "\n";

    // std::set<std::string> temp = keywords();
    // std::set<std::string>::iterator it = temp.begin();
    // while(it != temp.end()){
    //   os << *it;
    //   it++;
    // }
}


