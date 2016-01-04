#include "main_window.h"
#include <QApplication>
#include "db_parser.h"


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	Derived_DataStore ds; 

	DBParser parser;

  // Instantiate the individual product parsers we want
  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if(parser.parse(argv[1], ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

	PA2Layout window(&ds);
	window.show();

	return app.exec();
}
