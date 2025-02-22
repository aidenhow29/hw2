#include "util.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string testString = "Men's t-Shirt crew-fit";
    set<string> result = parseStringToWords(testString);

    cout << "Parsed words:" << endl;
    for (const string& word : result) {
        cout << word << endl;
    }

    return 0;
}