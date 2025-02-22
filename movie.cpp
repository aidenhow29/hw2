#include "util.h"
#include "product.h"
#include "movie.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating):
Product(category, name, price, qty),
genre_(genre),
rating_(rating) {

}

Movie::~Movie() {}


std::set<std::string> Movie:: keywords() const {
    
    std::set<std::string> returnSet;
    returnSet = parseStringToWords(genre_);
    std::set<std::string> tempSet;
    tempSet = parseStringToWords(name_);
    tempSet.insert(rating_);

    return returnSet;

}

std::string Movie:: displayString() const {

    std::string returnString = name_ + " " + std::to_string(price_) + " " + std::to_string(qty_) + " " + category_ + " " + genre_ + " " + rating_ + " ";
     
}

void Movie:: dump(std::ostream& os) const{
    os << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << std::to_string(qty_) << "\n" << category_ << "\n" << genre_ << "\n" << rating_ << "\n";
}


