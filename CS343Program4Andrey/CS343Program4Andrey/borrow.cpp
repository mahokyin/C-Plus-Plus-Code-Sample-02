// ------------------------------------------------- borrow.cpp --------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Implimentation of borrow operations for a particular customer, decreasing the stock of the movie and adding
//			 the history to the customer.
// ---------------------------------------------------------------------------------------------------------------------
#include "borrow.h"
#include <iostream>

using namespace std;

// ---------------------------------------Constructor-------------------------------------
// Description: Does all the nessesary checks if the customer can borrow this movie.
// PreCondition: Takes in an Inventory, History, customer ID, and Movie which are
//				 needed for the checks.
// PostCondition: Shows error message depending on the reason the movie cant be borrowed.
// ---------------------------------------------------------------------------------------
Borrow::Borrow(Inventory &inventory, History &history, int cusID, Movie &movie) {
	//Calls searchInventory for the movie
	this->inventory = &inventory;
	this->history = &history;
	stockHashNode = this->inventory->searchInventory(&movie);

	//Check if this is existing first
	if (stockHashNode == NULL) {
		status = false;

		//Provides error depending on the movie
		if (Classic *obj = dynamic_cast<Classic*>(&movie)) {
			reason = "Invalid Action: Classic video does not exist !";
		}
		else if (Drama *obj = dynamic_cast<Drama*>(&movie)) {
			reason = "Invalid Action: Drama video does not exist !";
		}
		else {
			reason = "Invalid Action: Comedy video does not exist !";
		}
		return;
	}

	//stock <= 0
	if (stockHashNode == NULL) return;
	if (stockHashNode->stock <= 0) {
		status = false;

		//Provides error depending on the movie
		if (Classic *obj = dynamic_cast<Classic*>(&movie)) {
			reason = "Invalid Action: There is no more classic video !";
		}
		else if (Drama *obj = dynamic_cast<Drama*>(&movie)) {
			reason = "Invalid Action: There is no more dramma video !";
		}
		else {
			reason = "Invalid Action: There is no more Classic video !";
		}
		return;
	}

	//Check if customer exist
	customer = history.searchCustomer(cusID);
	if (customer == NULL) {
		status = false;
		reason = "Invalid Action: invalid customer ID !";
		return;
	}
	
	//Check if customer are able to borrow
	if (customer == NULL) return;
	if (customer->canBorrow("B", stockHashNode->movie)) { //Call helper function
		status = true;
	}
	else {
		status = false;
		reason = "Customer can't borrow the same item !";
	}
}

// ---------------------------------------execute----------------------------------------
// Description: Calls either showError or addTransactionHistory depending on if the
//				movie can be borrowed or not.
// PreCondition: Constructor has to be implimented first, doing the nessesary checks
// PostCondition: Calls helper function
// --------------------------------------------------------------------------------------
void Borrow::execute() {
	if (!status) showError(); //Check status
	else {
		customer->addTransacionHistory("B", stockHashNode->movie); //Call helper
		stockHashNode->stock--; //Decrease stock of movie
	}
}

// --------------------------------------showError---------------------------------------
// Description: Displays error message depending on reason located from the constructor.
// PreCondition: Must be called from execute function.
// PostCondition: Error message is displayed.
// --------------------------------------------------------------------------------------
void Borrow::showError() {
	if (customer != NULL) //Display error depending on the reason
		cout << customer->firstName << " " << customer->lastName << "(" << customer->customerID << ") : ";
	cout << reason << endl;
}