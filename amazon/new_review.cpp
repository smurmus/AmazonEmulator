#include "new_review.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QDateEdit>
#include "review.h"
#include <QComboBox>
#include <QLabel>
#include <sstream>

using namespace std;

newReview::newReview(Derived_DataStore * ds, Product * p){

	setWindowTitle("Cart");

	data = ds;
	prod = p;

	layout = new QVBoxLayout;
	addReviewButton = new QPushButton("Add Review");

	//nameLabel = new QLabel("Name:");
	rateLabel = new QLabel("Rating:");
	dateLabel = new QLabel("Date:");
	textLabel = new QLabel("Review:");


	//name = new QLineEdit();
	rating = new QComboBox();
	date = new QDateEdit();
	text = new QTextEdit();

	for(int k = 0; k < 5; k++){
		rating -> addItem(QString::number(k + 1));
	}

	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(createReview()));
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(close()));


	//layout -> addWidget(nameLabel);
	//layout -> addWidget(name);

	layout -> addWidget(rateLabel);
	layout -> addWidget(rating);

	layout -> addWidget(dateLabel);	
	layout -> addWidget(date);

	layout -> addWidget(textLabel);	
	layout -> addWidget(text);

	layout -> addWidget(addReviewButton);

	setLayout(layout);

}

newReview::~newReview(){

}

void newReview::createReview(){


	string prodName, prodDate, reviewText, prodRate;
	int rate, year, month, day;

	prodName = prod -> getName();

	//creates combobox for user to choose from, holding numbers 1-5
	//rating -> setMaxCount(5);
	
	rate = (rating -> currentText()).toInt();

	year = (date -> date().year());
	month = (date -> date().month());
	day = (date -> date().day());

	stringstream ss;
	ss << year << "-";
	if(month < 10){ 
		ss << "0";
	}

	ss << month << "-";

	if(day < 10){
		ss << "0";
	}

	ss << day;
	
	prodDate = ss.str();

	//prodDate = year + "-" + month + "-" + day;

	reviewText = (text -> toPlainText()).toStdString();

	Review * aReview = new Review(prodName, rate, prodDate, reviewText); 

	data -> addReview(aReview);



}