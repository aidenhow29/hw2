#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //if less than two characters, drop
    //if contains punctuation, drop punctuation and proceeding characters
    //only if product name, book author, and clothing brand
    //rules don't apply for other key words (book ISBN and movie genre)

    set<string> mySet;
    // A (65)
    // Z (90)
    // a (97)
    // z (122)
    for(int i = 0; i < rawWords.length(); i++){
        int ascii = rawWords[i];
        //cout << ascii << endl;
        if(ascii < 65 || (ascii > 90 & ascii < 97) || ascii > 122){
          rawWords[i] = ' ';
        } 
    }
    stringstream ss(rawWords);
    string word;

    while (ss >> word) {
      if(word.length() > 1){
        mySet.insert(convToLower(word));
    }
    }
    return mySet;
}
    


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
