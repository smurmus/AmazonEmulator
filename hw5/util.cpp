#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <set>

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{
	std::stringstream ss;
	std::string word;
	//std::string str; //to check for substrings in punctuation
	int temp_size; //checks size of substring
	set<std::string> keywords; 

	ss << rawWord; 

	while(ss >> word){
		//check if ISBN number, while loop in case 2 ISBNs are next to each other
		/*while(isdigit(word[0] != 0)){
			keywords.insert(word);
			//parse in next 'word' after reading in number 
			ss >> word;
		}*/

		//not a number, so convert to lowercase
		word = convToLower(word);
		//remove all punctuation
		temp_size = 1;
		for(unsigned int i = 0; i < word.size(); i++){
			if(ispunct(word.c_str()[i]) != 0){
				if(temp_size <= 2 && i != 0){ //check for contractions in beginning
					word.erase(i - 1, 2); 
				}
				else if((word.substr(i + 1, word.size() - 1)).size() < 2){ //check for contractions at end
					word.erase(i, 2);
				}
				else if(word.substr(0, i - 1).size() >= 2){ //check for punctuation in the middle
					keywords.insert(word.substr(0, i - 1));
					keywords.insert(word.substr(i + 1, word.size() - 1));

				}
				else{
					word.erase(i, 1);
				}
				temp_size = 0;
			}
			temp_size++;
		}

		//check 
		if(word.size() >= 2){
			keywords.insert(word);
		}
	}

	return keywords;


}
