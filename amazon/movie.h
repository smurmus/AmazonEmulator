#include "product.h"
#include "util.h"

using namespace std;

class Movie : public Product{
	public:
		Movie(string genre, string rating, const string name, double price, int qty);
		~Movie();
		std::set<std::string> keywords() const;
		std::string displayString() const;
		void dump(std::ostream& os) const;	

	private:
		string genre;
		string rating;
};

