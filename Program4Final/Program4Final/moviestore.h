#ifndef MOVIESTORE_H
#define MOVIESTORE_H
#include <iostream>
#include <string>
#include "movie.h"
#include "customer.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "inventory.h"
#include "history.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class MovieStore
{
public:
	MovieStore(); //creates a new instance of MovieStore that is empty.
	MovieStore(ifstream &inputCustomer, ifstream &inputMovie); //creates a new instance of MovieStore that is empty.

	bool readCustomerData(ifstream &input);
	bool readMovieData(ifstream &input);
	void readCommandData(ifstream &input);


        //using the line taken from the text document.

	void displayAllCustomerHistory();

	void displayInventory();

    //bool returnMovie(string line); //takes the line that asks to return a movie to the store
        //and returns it if the values are valid.
    //bool borrowMovie(string line); //takes the line that asks to borrow a movie from the store
        //and borrows it if the values are valid.

private:

	Inventory inventory;
	History history;
};

#endif
