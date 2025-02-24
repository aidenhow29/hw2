#include "util.h"
#include "product.h"
#include "book.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author):
Product(category, name, price, qty),
author_(author),
ISBN_(ISBN) {

}

Book::~Book() {}

std::set<std::string> Book:: keywords() const {
    
    std::set<std::string> returnSet;
    returnSet = parseStringToWords(author_);
    std::set<std::string> tempSet;
    tempSet = parseStringToWords(name_);
    tempSet.insert(convToLower(ISBN_));

    returnSet.insert(tempSet.begin(), tempSet.end());
    

    return returnSet;
}

std::string Book:: displayString() const {
    std::stringstream ss("");
    ss << std::fixed << std:: setprecision(2) << price_;
    std::string returnString = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + ISBN_ + "\n" + ss.str() + " " + std::to_string(qty_) + " left.";
     
    return returnString;

}

void Book:: dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << std::to_string(qty_) << "\n" << ISBN_ << "\n" << author_ << "\n";
}


