// ------------------------------------------------- borrow.h ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Performs the borrow operation for a particular customer, decreasing the stock of the movie and adding
//			 the history to the customer. Child of Transaction class.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef BORROW_H
#define BORROW_H
#include "transaction.h"

using namespace std;

class Borrow : public Transaction 
{
public:
	// ---------------------------------------Constructor-------------------------------------
	// Description: Does all the nessesary checks if the customer can borrow this movie.
	// PreCondition: Takes in an Inventory, History, customer ID, and Movie which are
	//				 needed for the checks.
	// PostCondition: Shows error message depending on the reason the movie cant be borrowed.
	// ---------------------------------------------------------------------------------------
	Borrow(Inventory &inventory, History &history, int cusID, Movie &movie);

	// ---------------------------------------execute----------------------------------------
	// Description: Calls either showError or addTransactionHistory depending on if the
	//				movie can be borrowed or not.
	// PreCondition: Constructor has to be implimented first, doing the nessesary checks
	// PostCondition: Calls helper function
	// --------------------------------------------------------------------------------------
	virtual void execute();

	// --------------------------------------showError---------------------------------------
	// Description: Displays error message depending on reason located from the constructor.
	// PreCondition: Must be called from execute function.
	// PostCondition: Error message is displayed.
	// --------------------------------------------------------------------------------------
	virtual void showError();
};

#endif