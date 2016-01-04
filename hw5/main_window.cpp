#include "main_window.h"
#include <QString>
//#include "derived_datastore.h"
//#include <QListWidgetItem>
#include <QListWidget>
#include "user.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QApplication> 
#include <sstream>
#include <QWidget>
#include "product.h"
#include "util.h"
#include "review.h"
#include <fstream>
#include <iostream>
#include "msort.h"


using namespace std; 

//product names in ascending order
	struct AlphaStrComp {
	    bool operator()(Product * lhs, Product * rhs){
	    	/*if(strncmp(*lhs, *rhs, *lhs.size()) < 0){
	    		return true; //true since lhs is "smaller" alphabetically
	    	}
	    	return false;*/
	    	return lhs -> getName() < rhs -> getName();
	    }
	}; 


	//dates in descending order -> arguments will have to be .getDate of the products
	//is the opposite of alphacomp
	struct DateComp {
	    bool operator()(Review * lhs, Review * rhs) 
	    { // Uses string's built in operator< 
	      // to do lexicographic (alphabetical) comparison
	      return lhs -> date > rhs -> date;
	    }
	};

	//in descending order for ratings of 1-5...arguments will have to be .getRating of the product
	struct RatingComp{
		RatingComp(Derived_DataStore * data){
			ds = data;
		}

		Derived_DataStore * ds;

		bool operator()(Product * lhs, Product *rhs){
			return ds -> getAvgRating(rhs) <= ds -> getAvgRating(lhs); 
		}
	};

PA2Layout::PA2Layout(Derived_DataStore * data) {

	setWindowTitle("Welcome to Amazon!");

	database = data;

	//main layout
	layout = new QGridLayout();
	//all other layouts

	prodPlace = -1;
	position = -1;
	
	//search box layout (the top)
	searchlayout = new QHBoxLayout();
	
	prodLabel = new QLabel("Products:");
	revLabel = new QLabel("Reviews:");
	
	and_ = new QRadioButton("AND");
	or_ = new QRadioButton("OR");
	
	searchButton = new QPushButton("Search");

	searchBox = new QLineEdit("Enter search terms");

	searchlayout -> addWidget(searchButton);
	searchlayout -> addWidget(and_);
	searchlayout -> addWidget(or_);
	searchlayout -> addWidget(searchBox);

	//product/reviews layout
	prodRevLayout = new QVBoxLayout();
	productList = new QListWidget();
	reviewList = new QListWidget();

	prodRevLayout -> addWidget(prodLabel);
	prodRevLayout -> addWidget(productList);
	//display products when search is clicked
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchClicked()));


	prodRevLayout -> addWidget(revLabel);
	prodRevLayout -> addWidget(reviewList);
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(prodReviews(int)));

	//user layout
	userLayout = new QVBoxLayout();
	userLabel = new QLabel("Users:");
	userList = new QListWidget();
	//userProducts = new QListWidget();

	addCartButton = new QPushButton("Add to Cart");
	viewCartButton = new QPushButton("View Cart");

	for(unsigned int k = 0; k < (database -> getUsers()).size(); k++){
		userList -> addItem(QString::fromStdString(database -> getUsers()[k] -> getName()));

	}

	//add to cart or viewcart

	userLayout -> addWidget(userLabel);
	userLayout -> addWidget(userList);
	userLayout -> addWidget(addCartButton);
	//save index of chosen user 
	connect(userList, SIGNAL(currentRowChanged(int)), this, SLOT(userPos(int)));
	//save index of chosen product
	connect(productList, SIGNAL(currentRowChanged(int)), this, SLOT(prodPos(int)));
	//implement actual adding upon button clicking
	connect(addCartButton, SIGNAL(clicked()), this, SLOT(addToCart()));

	userLayout -> addWidget(viewCartButton);
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(PopOpen()));
	//layout -> addWidget(titleLabel);

	saveQuitLayout = new QHBoxLayout();

	//save and quit button
	addReviewButton = new QPushButton("Add Review");
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	saveQuitLayout -> addWidget(addReviewButton);

	sortByRatingButton = new QPushButton("Sort by Rating");
	connect(sortByRatingButton, SIGNAL(clicked()), this, SLOT(rateSort()));
	saveQuitLayout -> addWidget(sortByRatingButton);

	sortByNameButton = new QPushButton("Sort Alphabetically");
	connect(sortByNameButton, SIGNAL(clicked()), this, SLOT(nameSort()));
	saveQuitLayout -> addWidget(sortByNameButton);


	//save
	saveButton = new QPushButton("Save to File");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

	saveQuitLayout -> addWidget(saveButton);
	//quit

	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

	saveQuitLayout -> addWidget(quitButton);

	saveFile = new QLineEdit("Enter filename to save as");

	layout -> addLayout(searchlayout, 0, 0, 1, 8);
	layout -> addLayout(prodRevLayout, 1, 0, 4, 4);
	layout -> addLayout(userLayout, 1, 4, 4, 4);
	layout -> addLayout(saveQuitLayout, 5, 0, 1, 8);
	layout -> addWidget(saveFile, 6, 0, 1, 8);


	setLayout(layout);

}

PA2Layout::~PA2Layout(){
	/*delete prodLabel;
	delete revLabel;
	delete userLabel;

	delete searchButton;
	delete and_;
	delete or_;
	delete userList;
	delete searchBox;
	delete saveButton;
	delete quitButton;
	delete addCartButton;
	delete viewCartButton;

	delete saveQuitLayout;
	delete layout;
	delete searchlayout;
	delete userLayout;
	delete prodRevLayout;

	delete userList;
	delete reviewList;
	delete productList;

	delete userProducts;*/
}

//displays all products of a given search upon clicking "search"
void PA2Layout::searchClicked(){
	//clear listwidget for new search
	productList -> clear();

	stringstream ss((searchBox -> text()).toStdString()); 
	vector<string> terms;
	string term, price;

	//parses the search terms and goes to if statements to determine and/or
	while(ss >> term){
		terms.push_back(convToLower(term));
	}

	//in if statements do an addItem to the listWidget for products
	if(and_ -> isChecked()){
		prodList = database -> search(terms, 0);
	}
	else if(or_ -> isChecked()){
		prodList = database -> search(terms, 1);
	}
	
	//puts products' names and prices into the product list widget
	for(unsigned int k = 0; k < prodList.size(); k++){	
		productList -> addItem(QString::fromStdString(prodList[k] -> getName()) + "\n" + "$" + QString::number(prodList[k] -> getPrice()) + "\n" + "In stock: " + QString::number(prodList[k] -> getQty()) + "\n");
	}

}

//function that shows reviews of a product that has been clicked
void PA2Layout::prodReviews(int pos){

	while(reviewList -> count() > 0){
		reviewList -> takeItem(0);
	}

	vector<Review*> reviews = database -> getReviews(prodList[pos]);

	DateComp d;

	mergeSort(reviews, d);

	for(unsigned int k = 0; k < reviews.size(); k++){
		reviewList -> addItem("Rating: " + QString::number(reviews[k] -> rating) + "\n" + "Date: " + QString::fromStdString(reviews[k] -> date) + "\n" + "Review: " + QString::fromStdString(reviews[k] -> reviewText) + "\n");
	}


}

void PA2Layout::save(){

	ofstream ofile(((saveFile -> text()).toStdString()).c_str());
	database -> dump(ofile);
	ofile.close();

}

void PA2Layout::userPos(int p){

	position = p;
	//(database.getUsers())[p] 	
}

void PA2Layout::prodPos(int m){

	prodPlace = m;
}

void PA2Layout::addToCart(){
	if(position != -1 && prodPlace != -1){
	//returns chosen/clicked user
		database -> addCart((database -> getUsers())[position], prodList[prodPlace]);
	}
	//cout << database.getCart((database.getUsers())[position])[0];

	//userProducts -> addItem(QString::fromStdString(prodList[prodPlace] -> getName()) + "\n" + "$" + QString::number(prodList[prodPlace] -> getPrice()));

}

void PA2Layout::PopOpen(){

	//cout << position << "\n";

	if(position != -1){


		vector<User*> use = database -> getUsers();
		User * temp = use[position];

		PopUpDialog popUp(database, temp);

		popUp.exec();
	}

	productList -> clear();

	for(unsigned int k = 0; k < prodList.size(); k++){	
		productList -> addItem(QString::fromStdString(prodList[k] -> getName()) + "\n" + "$" + QString::number(prodList[k] -> getPrice()) + "\n" + "In stock: " + QString::number(prodList[k] -> getQty()) + "\n");
	}

}

void PA2Layout::addReview(){
	if(prodPlace != -1){

		Product * p = prodList[prodPlace];

		newReview aNewReview(database, p);
		aNewReview.exec();
	
		DateComp d;

		vector<Review*> r = database -> getAllReviews();

		mergeSort(r, d);

		for(unsigned int k = 0; k < r.size(); k++){
			reviewList -> addItem("Rating: " + QString::number(r[k] -> rating) + "\n" + "Date: " + QString::fromStdString(r[k] -> date) + "\n" + "Review: " + QString::fromStdString(r[k] -> reviewText));
		}

		reviewList -> clear();

	}

}

void PA2Layout::nameSort(){

		AlphaStrComp alph;

		mergeSort(prodList, alph);

		productList -> clear();


		///searchClicked();

		for(unsigned int k = 0; k < prodList.size(); k++){	
			productList -> addItem(QString::fromStdString(prodList[k] -> getName()) + "\n" + "$" + QString::number(prodList[k] -> getPrice()) + "\n" + "In stock: " + QString::number(prodList[k] -> getQty()) + "\n");
		}

}

void PA2Layout::rateSort(){

		RatingComp r(database);

		mergeSort(prodList, r);
		productList -> clear();

		for(unsigned int k = 0; k < prodList.size(); k++){	
			productList -> addItem(QString::fromStdString(prodList[k] -> getName()) + "\n" + "$" + QString::number(prodList[k] -> getPrice()) + "\n" + "In stock: " + QString::number(prodList[k] -> getQty()) + "\n" );
		}
}