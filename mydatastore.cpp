#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <iomanip>



MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){

    // iterate thru with an iterator? for loop?
    // clear out the dynamically allocated product & user pointers with detele

    for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }

    for (std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;  
    }

}

void MyDataStore::addProduct(Product* p){
    //insert p somewhere?

    products_.insert(p);
    std::set<std::string> keywords = p->keywords();

    // //debug
    // std::cout << "DEBUG: Adding product: " << p->getName() << " with keywords: ";


    for(const std:: string& keyword : keywords){
        std::cout << keyword << " ";
        keywordMap_[keyword].insert(p);

    }
}

void MyDataStore::addUser(User* u){
    //insert u in usersmap
    std::string username = convToLower(u->getName()); 
    users_[u->getName()] = u;

    // //debugging
    // std::cout << "DEBUG: Added user " << username << std::endl;


}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    // loop thru products, get keywords, put in a temp set?
    // compare that temp set to the term etc
    // 0 = AND search, 1 = OR search
    // retrun a vector>

    if(terms.empty()){
        return std::vector<Product*>() ; //edge
    } 


    std::set<Product*> result;
    // and search
    if(type == 0){
        result = keywordMap_[terms[0]];
        for(size_t i = 1; i < terms.size(); i++){
            result = setIntersection(result, keywordMap_[terms[i]]);
        }
    }
    //or search
    else { 
        for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); it++){
            result = setUnion(result, keywordMap_[*it]);
        }
    }


    return std::vector<Product*>(result.begin(), result.end());
}

void MyDataStore::dump(std::ostream& ofile){
    // similar to book, movie, clothing? 
    //os << name_ << "/n" << std::to_string(price_) << "n" << std::to_string(qty_) << "/n" << category_ << "/n" << brand_?

    ofile << "<products>" << std::endl;

    for(Product* p : products_){
        p->dump(ofile);
    }

    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;


    for(std::map<std::string, User*>::iterator it = users_.begin(); it!= users_.end(); it++){
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

//users_ getter func

std::map<std::string, User*> MyDataStore:: getUsers(){
    return users_;
}



