// --------------------------------------------- customer.cpp ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Implimentation of customers transaction history, borrow and return a movie.
// ---------------------------------------------------------------------------------------------------------------------
#include "customer.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

// -------------------------------Default Constructor-------------------------------------
// Description: Initializes the customer information
// ---------------------------------------------------------------------------------------
Customer::Customer() {
	customerID = 0;
	firstName = "N/A";
	lastName = "N/A";
	head = NULL;
}

// ------------------------------------Constructor---------------------------------------
// Description: Initializes the customer information
// PreCondition: Must get the customers id, first, last name.
// PostCondition: Info will be saved in the customer object.
// ---------------------------------------------------------------------------------------
Customer::Customer(int id, string firstname, string lastname) {
	this->customerID = id;
	this->firstName = firstname;
	this->lastName = lastname;
	head = NULL;
}

// ------------------------------------Destructor-----------------------------------------
// Description: Deletes memory that was allocated.
// PostCondition: All memory will be deleted.
// ---------------------------------------------------------------------------------------
Customer::~Customer() {
	// Delete linkedlist ptrs
	while (head != NULL) {
		HistoryData *oldNode = head;
		head = head->next;
		delete oldNode;
		oldNode = NULL;
	}
}

// ---------------------------addTransactionHistory---------------------------------------
// Description: Makes new history node and adds data to it.
// PreCondition: Must get the transaction type and movie object.
// PostCondition: Info will be saved as a new node.
// ---------------------------------------------------------------------------------------
void Customer::addTransacionHistory(string trans, Movie *movie)
{
	HistoryData *newHistory = new HistoryData; //new node
	newHistory->movie = movie;
	newHistory->transactionType = trans;
	newHistory->next = head;
	head = newHistory;
}

// ----------------------------------displayHistory---------------------------------------
// Description: Displays the customers borrow/return history.
// PostCondition: History will be displayed.
// ---------------------------------------------------------------------------------------
void Customer::displayHistory()
{
	//Cusomer has no history
	if (head == NULL) {
		cout << "No transaction history for " << this->firstName << " " << this->lastName << " (" << this->customerID << ")" << endl;
		return;
	}

	cout << endl;
	cout << "Transaction history for " << this->firstName << " " << this->lastName << " (" << this->customerID << ")" << endl;
	HistoryData *curr = head;
	while (curr != NULL) //While you are not at the end of the list
	{
		cout << curr->transactionType << " ";
		Classic *classic = dynamic_cast<Classic*>(curr->movie);

		//Check the genre of the movie
		if (classic == NULL)
		{
			//Print out drama's and comedy's information
			cout << curr->movie->getTitle() << ", " << curr->movie->getDirector() << ", " << curr->movie->getYear() << endl;
		}
		else
		{
			//Print out classics information
			cout << classic->getTitle() << ", " << classic->getDirector() << ", " << classic->getYear() << " " << classic->getMonth() << ", " << classic->getActor() << endl;
		}
		curr = curr->next; //Traverse the linked list
	}
}

// ------------------------------------canBorrow-----------------------------------------
// Description: Checks if the customer can borrow the movie depending on if they have 
//				returned it or not.
// PreCondition: Must get the transaction type and movie object.
// PostCondition: Returns a bool on if they can borrow or not.
// ---------------------------------------------------------------------------------------
bool Customer::canBorrow(string transType, Movie *movie) {
	if (head == NULL) return true;
	HistoryData *currPtr = head;
	while (currPtr != NULL) { //Loop through the customers history
		if (currPtr->transactionType == transType && currPtr->movie == movie) return false;
		if (currPtr->transactionType != transType && currPtr->movie == movie) return true;
		currPtr = currPtr->next;
	}
	return true;
}

// -------------------------------------canReturn-----------------------------------------
// Description: Checks if the customer can return the movie depending on if they have 
//				borrowed it or not.
// PreCondition: Must get the transaction type, movie object, and error message.
// PostCondition: Returns a bool on if they can return or not.
// ---------------------------------------------------------------------------------------
bool Customer::canReturn(string transType, Movie *movie, string *errorMsg) {
	if (head == NULL) return false;
	HistoryData *currPtr = head;
	while (currPtr != NULL) { //Loop through the customers history
		if (currPtr->transactionType == transType && currPtr->movie == movie) {
			*errorMsg = "Customer didn't return the same item"; //Save specific error message
			return false;
		}
		if (currPtr->transactionType != transType && currPtr->movie == movie) return true;
		currPtr = currPtr->next;
	}
	*errorMsg = "Customer didn't borrow this item before"; //Save specific error message
	return false;
}