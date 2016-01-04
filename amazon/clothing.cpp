//#include "product.h"
#include "clothing.h"
#include <set>
//#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Clothing::Clothing(string size_, string brand_, const string name_, double price_, int qty_):Product("clothing", name_, price_, qty_){
	size = size_;
	brand = brand_;
}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
	std::set<std::string> words = parseStringToWords(brand + " " + name_);
	words.insert(convToLower(size));
	return words; 
}

std::string Clothing::displayString() const{
	//change price and qty to strings
	stringstream oss;

	string p, q;

	oss << price_ << " " << qty_;
	oss >> p >> q; 

	string everything; 
	everything = "Name: " + name_ + "\n" + "Brand: " + brand + "\n" + "Size: " + size + "\n" + "Price: " + p + "\n" + "Quantity: " + q;
	return everything;
}

void Clothing::dump(std::ostream& os) const{
	os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" <<qty_ << "\n" << size << "\n" << brand << endl;
}
