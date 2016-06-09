// ------------------------------------------------- return.cpp --------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Implimentation of the return operation for a particular customer, increasing the stock of the movie and adding
//			 the history to the customer. Child of Transaction class.
// ---------------------------------------------------------------------------------------------------------------------
#include "return.h"
#include <iostream>

using namespace std;

// ---------------------------------------Constructor-------------------------------------
// Description: Does all the nessesary checks if the customer can return this movie.
// PreCondition: Takes in an Inventory, History, customer ID, and Movie which are
//				 needed for the checks.
// PostCondition: Shows error message depending on the reason the movie cant be returned.
// ---------------------------------------------------------------------------------------
Return::Return(Inventory &inventory, History &history, int cusID, Movie &movie)
{
	//Calls searchInventory helper
	this->inventory = &inventory;
	this->history = &history;
	stockHashNode = this->inventory->searchInventory(&movie);

	//Check if this is existing first
	if (stockHashNode == NULL) {
		status = false;

		//saves the specific error
		if (Classic *obj = dynamic_cast<Classic*>(&movie)) {
			reason = "Invalid Action: Classic video does not exist !";
		}
		else if (Drama *obj = dynamic_cast<Drama*>(&movie)) {
			reason = "Invalid Action: Drama video does not exist !";
		}
		else {
			reason = "Invalid Action: Classic video does not exist !";
		}
		return;
	}

	// Check if customer exist
	customer = history.searchCustomer(cusID); //Calls helper
	if (customer == NULL) {
		status = false;
		reason = "Invalid Action: invalid customer ID !";
		return;
	}

	// Check if customer are able to return
	if (customer == NULL) return;
	status = customer->canReturn("R", stockHashNode->movie, &reason);
}

// ---------------------------------------execute----------------------------------------
// Description: Calls either showError or addTransactionHistory depending on if the
//				movie can be returned or not.
// PreCondition: Constructor has to be implimented first, doing the nessesary checks
// PostCondition: Calls helper function
// --------------------------------------------------------------------------------------
void Return::execute() {
	if (!status) showError(); //Calls error helper
	else { //else add movie to customer histor and increase the stock
		customer->addTransacionHistory("R", stockHashNode->movie);
		stockHashNode->stock++;
	}
}

// --------------------------------------showError---------------------------------------
// Description: Displays error message depending on reason located from the constructor.
// PreCondition: Must be called from execute function.
// PostCondition: Error message is displayed.
// --------------------------------------------------------------------------------------
void Return::showError() {
	if (customer != NULL) //Print error which was located in the constructor
		cout << customer->firstName << " " << customer->lastName << "(" << customer->customerID << ") : ";
	cout << reason << endl;
}


