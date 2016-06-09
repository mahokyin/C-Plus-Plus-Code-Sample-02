// ------------------------------------------------ history.h ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - History class has functions to add a customer to the customer hash table and search, and display customers.
// ---------------------------------------------------------------------------------------------------------------------
#include "customer.h"
using namespace std;

class History
{
public:
	// ---------------------------------------Constructor-------------------------------------
	// Description: Initializes the customer hash table.
	// ---------------------------------------------------------------------------------------
	History();

	// ---------------------------------------Destructor--------------------------------------
	// Description: Deletes all the memory allocated in history.cpp.
	// PostCondition: All memory will be released.
	// ---------------------------------------------------------------------------------------
	~History();

	// --------------------------------------addCustomer--------------------------------------
	// Description: Adds a customer to the customer hash table
	// PreCondition: Takes in a customer as a parameter.
	// PostCondition: New customer will be added to the hash table.
	// ---------------------------------------------------------------------------------------
	bool addCustomer(Customer *customer); 

	// ----------------------------displayCustomerHistory-------------------------------------
	// Description: Calls helper function to display the history.
	// PreCondition: Takes in a customers ID as a mparameter.
	// ---------------------------------------------------------------------------------------
	void displayCustomerHistory(int custID);

	// -----------------------------------searchCustomer-------------------------------------
	// Description: Returns the customer object based on their ID from the hash table.
	// PreCondition: Takes in a customers ID as a mparameter.
	// PostCondition: Returns customer object.
	// ---------------------------------------------------------------------------------------
	Customer* searchCustomer(int cusID);
private:
	//Hash table of customer objects, key is the customers ID
	Customer *customerHashtable[10000];
};
