#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include <QRadioButton>
#include "derived_datastore.h"
#include <QListWidget>
#include <QLineEdit>
#include <QGridLayout>
#include "pop_up.h"
#include "user.h"
#include "new_review.h"


class PA2Layout : public QWidget{
	Q_OBJECT

	public:
		PA2Layout(Derived_DataStore * data);
		~PA2Layout();

	private slots:
		void searchClicked();
		void prodReviews(int pos);
		void save();
		void addToCart();
		void userPos(int p);
		void prodPos(int m);
		void PopOpen();
		void addReview();
		void nameSort();
		void rateSort();

	private:

		int position;
		int prodPlace;
		//bool sorted;
		//bool r_sorted;

		QGridLayout* layout;
		QHBoxLayout* searchlayout;
		QHBoxLayout* saveQuitLayout;
		QVBoxLayout* prodRevLayout;
		QVBoxLayout* userLayout;

		QPushButton* searchButton;
		QPushButton* addCartButton;
		QPushButton* viewCartButton;
		QPushButton* quitButton;
		QPushButton* saveButton;
		QPushButton* addReviewButton;
		QPushButton* sortByRatingButton;
		QPushButton* sortByNameButton;


		QRadioButton* and_;
		QRadioButton* or_;

		QLabel* prodLabel;
		QLabel* revLabel;
		QLabel* userLabel;

		QLineEdit * searchBox;
		QListWidget * userList;
		QListWidget * productList;
		QListWidget * reviewList;
		QLineEdit * saveFile;

		Derived_DataStore * database;
		vector<Product*> prodList;
		vector<User*> users; 

};

#endif