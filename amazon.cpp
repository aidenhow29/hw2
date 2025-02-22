#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "mydatastore.h"
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

using namespace std;

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};


void displayProducts(vector<Product*>& hits);


std::map<std::string, std::vector<Product*>> userCart; 
std::map<std::string, User*> users;


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    //debugging
    std::ifstream testFile(argv[1]);
    if (!testFile) {
    std::cerr << "ERROR: Could not open " << argv[1] << std::endl;
    return 1;
    }
    std::cout << "DEBUG: Opened database file successfully!\n";
    testFile.close();


    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "DEBUG: Finished parsing. Total Users: " << ds.getUsers().size() << endl;
    users = ds.getUsers();

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;

        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }

              /* debug */  cout << "DEBUG: Searching for (AND): ";
                for (const string& t : terms) cout << t << " ";
                cout << endl;


                hits = ds.search(terms, 0);
                displayProducts(hits);
            }

            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }

                /* debug */  cout << "DEBUG: Searching for (OR): ";
                for (const string& t : terms) cout << t << " ";
                cout << endl;

                hits = ds.search(terms, 1);
                displayProducts(hits);
            }

            else if ( cmd == "ADD" ) { //done
                string username;
                int hitIndex;
                if(ss >> username >> hitIndex){
                    if(hitIndex <= 0 || hitIndex > static_cast<int>(hits.size())){
                        cout << "Invalid request" << endl;
                    }
                    else{
                        userCart[username].push_back(hits[hitIndex - 1]);
                        cout << "Added to cart" << endl;
                    }
                }
                else{
                    cout << "Invalid request" << endl;
                }
            }

            else if ( cmd == "VIEWCART" ){ //done
                string username;
                if(ss >> username) {
                    if(userCart.find(username) == userCart.end() || userCart[username].empty()){
                        cout << "Cart is empty!" << endl;
                    }
                    else{
                        cout << username << "'s Cart:" << endl;
                        int count = 1;
                        for(Product* p: userCart[username]){
                            cout << "Item " << count << ":" << endl;
                            cout << p->displayString() << endl;
                            cout << endl;
                            count++;
                        }
                    }
                    
                }
                else{
                    cout << "Invalid username" << endl;
                }
            }

            else if ( cmd == "BUYCART" ){ // done
                string username;
                if(ss >> username){
                    if (userCart.find(username) == userCart.end()){
                        cout << "Invalid username" << endl;
                    }
                    else if(userCart[username].empty()){
                        cout << "Cart is empty!" << endl;
                    }
                    else{
                        User* user = users[username];
                        vector<Product*>& cart = userCart[username];
                        vector<Product*> remainingCart;

                        for(Product* p : cart){
                            if(p->getQty() > 0 && user->getBalance() >= p->getPrice()){
                                p->subtractQty(1);
                                user->deductAmount(p->getPrice());
                                cout << "Purchased: " << p->getName() << endl;
                            }
                            else{
                                remainingCart.push_back(p);
                            }
                        }

                        cart = remainingCart;
                    }
                }
                else{
                    cout << "Invalid username" << endl;
                }
            }

            else if ( cmd == "QUIT")  { 
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            
            }
	    /* Add support for other commands here */




            else {
                cout << "Unknown command" << endl;
            }
        }
    
        
    return 0;

    }


void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
