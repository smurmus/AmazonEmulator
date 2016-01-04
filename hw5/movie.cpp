//#include "product.h"
#include "movie.h"
#include <set>
//#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Movie::Movie(string genre_, string rating_, const string name_, double price_, int qty_):Product("movie", name_, price_, qty_){
	genre = genre_;
	rating = rating_;
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
	std::set<std::string> words = parseStringToWords(name_);
	words.insert(convToLower(genre));
	words.insert(rating);
	return words; 
}

std::string Movie::displayString() const{
	//change price and qty to strings
	stringstream oss;

	string p, q;

	oss << price_ << " " << qty_;
	oss >> p >> q; 

	string everything; 
	everything = "Name: " + name_ + "\n" + "Genre: " + genre + "\n" + "Rating: " + rating + "\n" + "Price: " + p + "\n" + "Quantity: " + q;
	return everything;
}

void Movie::dump(std::ostream& os) const{
	os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre << "\n" << rating << endl;
}
