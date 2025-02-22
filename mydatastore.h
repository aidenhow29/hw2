#include "datastore.h"
#include "product.h"
#include "user.h"
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

class MyDataStore : public DataStore{

    public:
    MyDataStore();
    ~MyDataStore();

    std::map<std::string, User*> getUsers();

    void addProduct(Product* p);        // inherited from dataStore (pure virtual)
   
    void addUser(User* u);      // inherited from dataStore (pure virtual)

    std::vector<Product*> search(std::vector<std::string>& terms, int type);    // inherited from dataStore (pure virtual)

    void dump(std::ostream& ofile);     //inherited from dataStore (pure virtual)

    private:
    std::set<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_;

};
