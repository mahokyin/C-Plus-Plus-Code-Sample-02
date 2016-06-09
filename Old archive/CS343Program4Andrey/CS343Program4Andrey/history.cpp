// ---------------------------------------------- history.cpp ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - History class has functions to add a customer to the customer hash table and search, and display customers.
// ---------------------------------------------------------------------------------------------------------------------
#include "history.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// ---------------------------------------Constructor-------------------------------------
// Description: Initializes the customer hash table.
// ---------------------------------------------------------------------------------------
History::History()
{
	//Loop through entire hash table
	for (int i = 0; i < 10000; i++)
		customerHashtable[i] = NULL;
}

// ---------------------------------------Destructor--------------------------------------
// Description: Deletes all the memory allocated in history.cpp.
// PostCondition: All memory will be released.
// ---------------------------------------------------------------------------------------
History::~History() {
	//Loop through entire hash table
	for (int i = 0; i < 10000; i++) {
		if (customerHashtable[i] != NULL) {
			Customer *oldPtr = customerHashtable[i];
			delete oldPtr; oldPtr = NULL; //Delete pointer
		}
	}
	delete[] customerHashtable; //delete hash table
}

// --------------------------------------addCustomer--------------------------------------
// Description: Adds a customer to the customer hash table
// PreCondition: Takes in a customer as a parameter.
// PostCondition: New customer will be added to the hash table.
// ---------------------------------------------------------------------------------------
bool History::addCustomer(Customer *customer) {
	//Checks the customers id
	if (customerHashtable[customer->customerID] == NULL) {
		customerHashtable[customer->customerID] = customer;
		return true;
	}
	else {
		cout << "Invalid Customer ID" << endl;
	}
}

// ----------------------------displayCustomerHistory-------------------------------------
// Description: Calls helper function to display the history.
// PreCondition: Takes in a customers ID as a mparameter.
// ---------------------------------------------------------------------------------------
void History::displayCustomerHistory(int custID)
{
	//Call helper function
	customerHashtable[custID]->displayHistory();
}

// -----------------------------------searchCustomer-------------------------------------
// Description: Returns the customer object based on their ID from the hash table.
// PreCondition: Takes in a customers ID as a mparameter.
// PostCondition: Returns customer object.
// ---------------------------------------------------------------------------------------
Customer* History::searchCustomer(int cusID) {
	return customerHashtable[cusID];
}



