#include "product.h"
#include "util.h"

using namespace std;

class Clothing : public Product{
	public:
		Clothing(string size, string brand, const string name, double price, int qty);
		~Clothing();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;	

	private:
		string size;
		string brand;

};

