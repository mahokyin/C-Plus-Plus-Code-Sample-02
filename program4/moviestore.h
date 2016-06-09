// ------------------------------------------------ moviestore.h --------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - MovieStore functions that will read the files and break them up
// ---------------------------------------------------------------------------------------------------------------------
#ifndef MOVIESTORE_H
#define MOVIESTORE_H
#include "movie.h"
#include "customer.h"
#include "classic.h"
#include "borrow.h"
#include "return.h"
#include "comedy.h"
#include "drama.h"
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
	// ------------------------------------Default Constructor--------------------------------
	MovieStore(); 

	// ---------------------------------------Constructor-------------------------------------
	// Description: creates a new instance of MovieStore that is empty. Provides messages
	//				for the success or failure of reading the files.
	// PreCondition: Takes in 2 ifstream files, customer data and movie data
	// ---------------------------------------------------------------------------------------
	MovieStore(ifstream &inputCustomer, ifstream &inputMovie);

	// ----------------------------------readCustomerData ------------------------------------
	// Description: Reads the customer file and breaks the file up, organizing the data
	// preconditions: customer file must be saved in same folder as .h and .cpp files
	// postconditions: customer object will be made for correct info from the file, or
	//				   error message will be displayed.
	// ---------------------------------------------------------------------------------------
	bool readCustomerData(ifstream &input);

	// -----------------------------------readMovieData --------------------------------------
	// Description: Reads the movie file and breaks the file up, organizing the data
	// preconditions: movie file must be saved in same folder as .h and .cpp files
	// postconditions: movie object will be made for correct info from the file, or
	//				   error message will be displayed.
	// ---------------------------------------------------------------------------------------
	bool readMovieData(ifstream &input);

	// -----------------------------------readCommandData ------------------------------------
	// Description: Reads the command file and breaks the file up, organizing the data
	// preconditions: command file must be saved in same folder as .h and .cpp files
	// postconditions: One of 4 actions will be performed (Borrow, Return, History, Inventory)
	//				   or error message will be displayed.
	// ---------------------------------------------------------------------------------------
	void readCommandData(ifstream &input);
private:
	Inventory inventory;
	History history;
};

#endif
