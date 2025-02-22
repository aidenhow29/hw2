#include "util.h"
#include "product.h"
#include <string>
#include <iostream>
#include <set>

class Book: public Product{
    public:
    Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
    ~Book();

    std::set<std::string> keywords() const;

    std::string displayString() const;

    virtual void dump(std::ostream& os) const;

    private:
    std::string ISBN_;
    std::string author_; 
    

};

