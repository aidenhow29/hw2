#include "util.h"
#include "product.h"
#include <string>
#include <iostream>
#include <set>

class Movie: public Product{
    public:
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    ~Movie();

    std::set<std::string> keywords() const;

    std::string displayString() const;

    virtual void dump(std::ostream& os) const;

    private:
    std::string genre_;
    std::string rating_; 
    

};

