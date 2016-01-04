#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include "derived_datastore.h"
#include <map>
#include <deque>
#include <review.h> 

using namespace std;

/*Derived_DataStore::Derived_DataStore(vector<Product*>, vector<User*>):DataStore(){
	products = products;
	users = users;
}*/

Derived_DataStore::Derived_DataStore(){

}


Derived_DataStore::~Derived_DataStore(){ 
	for(unsigned int i = 0; i < products.size(); i++){ //delete all new products
		delete products[i];
	}
	for(unsigned int k = 0; k < users.size(); k++){ //delete all new users 
		delete users[k];
	}
	for(unsigned int j = 0; j < reviews.size(); j++){
		delete reviews[j];
	}


}

void Derived_DataStore::addProduct(Product* p){
	set<string> keywordSet;
	products.push_back(p); //put all products in a vector
	keywordSet = p -> keywords(); //create a set containing the keywords of each product as element

	set<string>::iterator it; 
  	for (it = keywordSet.begin(); it != keywordSet.end(); ++it){ //iterate through a set 
  		myMap[*it].insert(p); //insert product into the set of products associated with it (through a map)
  	}
}

void Derived_DataStore::addUser(User* u){
	users.push_back(u);

}

//returns user given the username

User* Derived_DataStore::getUser(string name){ //give the user since we only have username
	User* u; 
	for(unsigned int i = 0; i < users.size(); i++){
		if(users[i] -> getName() == name){
			u = users[i];
			return u;
		}
	}
return NULL;
}


//returns the cart of a user given the username

void Derived_DataStore::addCart(User* u, Product* p){
	cart[u].push_back(p);
}

void Derived_DataStore::removeCart(User* u, int iter){
	cart[u].erase(cart[u].begin() + iter);
}

void Derived_DataStore::displayCart(User* u){
	deque<Product*> temp = cart[u];
	for(unsigned int i = 0; i < temp.size(); i++){
		cout << i + 1 << ": " << endl;
		cout << temp[i] -> displayString() << endl;
	}
}

deque<Product*> Derived_DataStore::getCart(User* u){
	return cart[u];
}


vector<Product*> Derived_DataStore::search(vector<string>& terms, int type){
	set<Product*> data; 
	vector<Product*> allProds;
	vector< set<Product*> > sets; //contains all the different sets of products for each search term
	for(unsigned int i = 0; i < terms.size(); i++){ //iterates through terms
		sets.push_back(myMap[terms[i]]); //creates set containing each term and puts it in vector
	}

	data = sets[0]; //"base" set to compare to

	for(unsigned int k = 0; k < sets.size(); k++){ 
		if(type == 0){ //AND search
			data = setIntersection(data, sets[k]); //changes data for every other set it is compared, each time
		}
		else{ //OR search
			data = setUnion(data, sets[k]); //changes data as above
		}

	}

	//iterate through final set of union/intersection and put all found products into vector to return 
	set<Product*>::iterator it;
  	for (it = data.begin(); it != data.end(); ++it){
  		allProds.push_back(*it);
  	}

  	return allProds;
}

void Derived_DataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	for(unsigned int i = 0; i < products.size(); i++){
		products[i] -> dump(ofile);
		//ofile << endl;
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl; 
	for(unsigned int k = 0; k < users.size(); k++){
		users[k] -> dump(ofile);
		//ofile << "\n";
	}
	ofile << "</users>" << endl; 
	ofile << "<reviews>" << endl;

	vector<Review*> temp;

	vector<Product*>::iterator it;
  	for (it = products.begin(); it != products.end(); ++it){
		temp = prodReviews[*it];
		for(unsigned int j = 0; j < temp.size(); j++){
			ofile << temp[j] -> prodName << "\n";
			ofile << temp[j] -> rating << " " << temp[j] -> date << " " << temp[j] -> reviewText << endl;
		} 
		//ofile << "\n";
	}
	ofile << "</reviews>" << endl;
}

vector<User*> Derived_DataStore::getUsers(){
	return users;
}

void Derived_DataStore::addReview(Review * r){
	reviews.push_back(r);
	//string pName = "";
	//Product * temp;

	//find the product that has the same name as the one associated with the review being added
	for(unsigned int k = 0; k < products.size(); k++){
		if(convToLower(products[k] -> getName()) == convToLower(r -> prodName)){
			//pName = products[k] -> getName();
			//temp = products[k];
			prodReviews[products[k]].push_back(r);
			return;
		}
	}
}

vector<Review*> Derived_DataStore::getReviews(Product* p){
	return prodReviews[p];
}

vector<Review*> Derived_DataStore::getAllReviews(){
	return reviews;
}

double Derived_DataStore::getAvgRating(Product* a){
	double sum = 0;
	int size = prodReviews[a].size();

	for(int k = 0; k < size; k++){
		sum += (prodReviews[a])[k] -> rating;
	}

	if(size == 0){
		return 0;
	}

	return sum/size;

}

void Derived_DataStore::buyCart(User * person){
	int temp_pos = 0;

	Product * p; 
	for(unsigned int k = 0; k < (getCart(person)).size(); k++){
		if(temp_pos >= (getCart(person)).size()){
			return;
		}
		p = (getCart(person))[temp_pos];
		if((p -> getQty() > 0) && (person -> getBalance() >= p -> getPrice())){
			p -> subtractQty(1); //decrease quantity
			person -> deductAmount(p -> getPrice()); //reduce user's balance
			removeCart(person, temp_pos); //remove from user's cart
			//k--;
		}
		else{
			temp_pos++;
		}
	}
}



	/*set<Product*>::iterator it; 
  	for (it = prodSet.begin(); it != prodSet.end(); ++it){ //iterate through a set 
  		prodReviews[*it].insert(r); //insert review into the set of reviews associated with it (through a map)
  	}*/
  	 
