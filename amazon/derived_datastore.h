#ifndef DERIVED_DATASTORE_H
#define DERIVED_DATASTORE_H

#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <map>
#include "user.h"
#include <deque> 

using namespace std;

class Derived_DataStore : public DataStore{
	public:
		//Derived_DataStore(vector<Product*>, vector<User*>);
		Derived_DataStore();
		~Derived_DataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		vector<Product*> search(vector<string>& terms, int type);
		void dump(std::ostream& ofile);
		
		//adds products to cart given user
		void addCart(User* u, Product* p);
		//removes products from cart given user
		void removeCart(User* u, int iter);
		//display given user's cart
		void displayCart(User* u);
		//return a user's cart to be able to access individual products and its variables (price, qty)
		deque<Product*> getCart(User* u);
		//give the user bc we only input a string username
		User* getUser(string name);

		vector<User*> getUsers();

		double getAvgRating(Product* a);
		vector<Review*> getReviews(Product* p);
		vector<Review*> getAllReviews();
		//add reviews!!

		void addReview(Review* r);
		void buyCart(User * u);
		
	private:
		//int temp_pos;

		vector<Product*> products;
		vector<User*> users;
		vector<Review*> reviews; 
		map<Product*, vector<Review*> > prodReviews; 
		map<string, set<Product*> > myMap;
		map<User*, deque<Product*> > cart;
};
#endif