#include "product.h"
#include "util.h"

using namespace std;

class Book : public Product{
	public:
		Book(string author, string ISBN, const string name, double price, int qty);
		~Book();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;	

	private:
		string author;
		string ISBN;

};

