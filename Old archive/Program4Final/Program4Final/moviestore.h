#ifndef MOVIESTORE_H
#define MOVIESTORE_H
#include "movie.h"
#include "customer.h"
#include "classic.h"
#include "borrow.h"
#include "return.h"
#include "comedy.h"
#include "drama.h"
//#include "inventory.h"
//#include "history.h"
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include<iomanip>

using namespace std;

class MovieStore
{
public:
	MovieStore(); //creates a new instance of MovieStore that is empty.
	MovieStore(ifstream &inputCustomer, ifstream &inputMovie); //creates a new instance of MovieStore that is empty.

	bool readCustomerData(ifstream &input);
	bool readMovieData(ifstream &input);
	void readCommandData(ifstream &input);

private:

	Inventory inventory;
	History history;
};

#endif
