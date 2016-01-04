#ifndef POP_UP_H
#define POP_UP_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "product.h"
#include "user.h"
#include "derived_datastore.h"
#include <QLabel>
#include <QGridLayout>

using namespace std; 

class PopUpDialog : public QDialog{
	Q_OBJECT

public:
	PopUpDialog(Derived_DataStore * ds, User * u);
	~PopUpDialog();

private slots:
	void buyCart();
	void remove();
	void productIndex(int index);

private:

	int prodIndex;
	User * person;
	//int temp_pos;
	//int iter;

	deque<Product*> cart;

	QGridLayout * overallLayout;
	QHBoxLayout * buttonsLayout;

	QPushButton * buyCartButton;
	QPushButton * removeButton; 

	QListWidget * userProducts;

	QLabel * titleLabel;

	Derived_DataStore * data;

	//QListWidget * list;

};
#endif