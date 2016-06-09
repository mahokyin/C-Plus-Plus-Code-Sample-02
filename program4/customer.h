// ----------------------------------------------- customer.h ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to a customers transaction history, borrow and return a movie, includes customers data, and 
//			 a struct that will be used as a node in the history data, which is a linked list.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include "movie.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

using namespace std;

class Customer
{
public:
	// -------------------------------Default Constructor-------------------------------------
	// Description: Initializes the customer information
	// ---------------------------------------------------------------------------------------
	Customer();

	// ------------------------------------Constructor---------------------------------------
	// Description: Initializes the customer information
	// PreCondition: Must get the customers id, first, last name.
	// PostCondition: Info will be saved in the customer object.
	// ---------------------------------------------------------------------------------------
	Customer(int, string, string);

	// ------------------------------------Destructor-----------------------------------------
	// Description: Deletes memory that was allocated.
	// PostCondition: All memory will be deleted.
	// ---------------------------------------------------------------------------------------
	~Customer();

	//Customers data, recieved from text file
	int customerID;
	string firstName;
	string lastName;

	// ---------------------------addTransactionHistory---------------------------------------
	// Description: Makes new history node and adds data to it.
	// PreCondition: Must get the transaction type and movie object.
	// PostCondition: Info will be saved as a new node.
	// ---------------------------------------------------------------------------------------
	void addTransacionHistory(string trans, Movie *movie);

	// ----------------------------------displayHistory---------------------------------------
	// Description: Displays the customers borrow/return history.
	// PostCondition: History will be displayed.
	// ---------------------------------------------------------------------------------------
	void displayHistory();

	// ------------------------------------canBorrow-----------------------------------------
	// Description: Checks if the customer can borrow the movie depending on if they have 
	//				returned it or not.
	// PreCondition: Must get the transaction type and movie object.
	// PostCondition: Returns a bool on if they can borrow or not.
	// ---------------------------------------------------------------------------------------
	bool canBorrow(string transType, Movie *movie);

	// -------------------------------------canReturn-----------------------------------------
	// Description: Checks if the customer can return the movie depending on if they have 
	//				borrowed it or not.
	// PreCondition: Must get the transaction type, movie object, and error message.
	// PostCondition: Returns a bool on if they can return or not.
	// ---------------------------------------------------------------------------------------
	bool canReturn(string transType, Movie *movie, string *errorMsg);
private:
	//This struct is used as the nodes in the history linked list
	struct HistoryData
	{
		string transactionType;    //Either borrowed or retuned
		Movie *movie = NULL;	   //All the info about the particular movie
		HistoryData *next = NULL;  //Next pointer
	};

	HistoryData *head = NULL; //Points to head of the linked list
};

#endif
