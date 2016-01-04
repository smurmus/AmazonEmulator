#include "pop_up.h"
#include <QPushButton>
#include "product.h"
#include <QListWidget>
#include "user.h"
#include <iostream>
#include <QWidget>

using namespace std;

PopUpDialog::PopUpDialog(Derived_DataStore * ds, User * u){

	setWindowTitle("Cart");

	overallLayout = new QGridLayout();
	buttonsLayout = new QHBoxLayout();

	//QLabel * resultLabel = new QLabel ();
	//overallLayout → addWidget(resultLabel);
	data = ds;

	cart = data -> getCart(person);
	person = u;
	//temp_pos = 0;

	//iter = cart.size();

	prodIndex = -1;

	//cout << cart[0] -> getName();

	//titleLabel = new QLabel(QString::fromStdString(person -> getName()) + "'s Cart");
	userProducts = new QListWidget();

	buyCartButton = new QPushButton("Buy Cart");
	connect(buyCartButton, SIGNAL(clicked()), this, SLOT(buyCart()));


	removeButton = new QPushButton("Remove");	
	//save product chosen to remove
	connect(userProducts, SIGNAL(currentRowChanged(int)), this, SLOT(productIndex(int)));
	connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));



	//cout << cart.size() << endl;
	for(unsigned int k = 0; k < data -> getCart(person).size(); k++){
		userProducts -> addItem(QString::fromStdString(data -> getCart(person)[k] -> getName()) + "\n" + "$" + QString::number(data -> getCart(person)[k] -> getPrice()));
	}

	buttonsLayout -> addWidget(buyCartButton);//, 0, 0, 1, 2);
	buttonsLayout -> addWidget(removeButton);//, 0, 4, 1, 2);

	//overallLayout -> addWidget(titleLabel);
	overallLayout -> addWidget(userProducts);//, 0, 0, 4, 4);

	overallLayout -> addLayout(buttonsLayout, 4, 0);


	setLayout(overallLayout);

}

PopUpDialog::~PopUpDialog(){
	/*delete overallLayout;
	delete buttonsLayout;
	delete buyCartButton;
	delete removeButton;*/
}

void PopUpDialog::productIndex(int index){
	prodIndex = index;
}

void PopUpDialog::buyCart(){
	//check if able to buy the item
	data -> buyCart(person);

	userProducts -> clear();

	for(unsigned int k = 0; k < data -> getCart(person).size(); k++){
		userProducts -> addItem(QString::fromStdString(data -> getCart(person)[k] -> getName()) + "\n" + "$" + QString::number(data -> getCart(person)[k] -> getPrice()));
	}


	/*//int iter = user_cart.size();
	//make sure to go through all products to buy all possible
	while(iter > 0){
		//check conditions for being able to buy, then proceed
		//user at specific position
		p = (data -> getCart(person))[temp_pos];
		if((p -> getQty() > 0) && (person -> getBalance() >= p -> getPrice())){
			p -> subtractQty(1); //decrease quantity
			person -> deductAmount(p -> getPrice()); //reduce user's balance
			data -> removeCart(person, temp_pos); //remove from user's cart
			userProducts -> takeItem(temp_pos); //remove from list widget
		}
		//if can't buy, increment temp_pos to look at next product 
		else{
			temp_pos++;
		}
		iter--;
	}*/

}

void PopUpDialog::remove(){

	if(prodIndex != -1){
		//remove from actual user's cart
		data -> removeCart(person, prodIndex);
		//remove from list widget holding list of products
		//userProducts -> takeItem(prodIndex);
		userProducts->clear();
		for(unsigned int k = 0; k < data -> getCart(person).size(); k++){
		userProducts -> addItem(QString::fromStdString(data -> getCart(person)[k] -> getName()) + "\n" + "$" + QString::number(data -> getCart(person)[k] -> getPrice()));
	}



	}

}