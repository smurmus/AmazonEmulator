#ifndef NEW_REVIEW_H
#define NEW_REVIEW_H


#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include "derived_datastore.h"
#include <QDateEdit>
#include <QComboBox>
#include <QLabel>
#include "product.h"

using namespace std;

class newReview : public QDialog{
	Q_OBJECT

public:
	newReview(Derived_DataStore * ds, Product * p);
	~newReview();

private slots:
	void createReview();
	
private:
	QPushButton* addReviewButton;

	//QLabel * nameLabel;
	QLabel * rateLabel;
	QLabel * dateLabel;
	QLabel * textLabel;

	QVBoxLayout* layout;
	//QLineEdit* name;
	QTextEdit* text;

	QDateEdit * date;

	QComboBox* rating;

	Derived_DataStore * data;
	Product * prod;

	//Review * r; 
};
#endif