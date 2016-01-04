//#include "product.h"
#include "book.h"
#include <set>
//#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Book::Book(string author_, string ISBN_, const string name_, double price_, int qty_):Product("book", name_, price_, qty_){
	ISBN = ISBN_;
	author = author_;
}

Book::~Book(){

}

set<string> Book::keywords() const{
	set<string> words = parseStringToWords(author + " " + name_);
	words.insert(ISBN);
	return words; 
}

std::string Book::displayString() const{
	//change price and qty to strings
	stringstream oss;

	string p, q;

	oss << price_ << " " << qty_;
	oss >> p >> q; 

	string everything; 
	everything = "Name: " + name_ + "\n" + "Author: " + author + "\n" + "ISBN: " + ISBN + "\n" + "Price: " + p + "\n" + "Quantity: " + q;
	return everything;
}

void Book::dump(std::ostream& os) const{
	os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN << "\n" << author << endl;
}
