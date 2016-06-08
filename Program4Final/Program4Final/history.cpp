//#include "transaction.h"
#include "history.h"
//#include "customer.h"
//#include "moviestore.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

History::History()
{

	for (int i = 0; i < 10000; i++)
		customerHashtable[i] = NULL;

	cout << "Initilize the customerHashtable successfully !" << endl;
}

History::~History() {
	for (int i = 0; i < 10000; i++) {
		if (customerHashtable[i] != NULL) {
			Customer *oldPtr = customerHashtable[i];
			delete oldPtr; oldPtr = NULL;
			//customerHashtable[i] = NULL;
		}
	}
	delete[] customerHashtable;
}

bool History::addCustomer(Customer *customer) {
	if (customerHashtable[customer->customerID] == NULL) {
		customerHashtable[customer->customerID] = customer;
		return true;
	}
	else {
		cout << "Invalid Customer ID" << endl;
	}
}

void History::displayCustomerHistory(int custID)
{
	customerHashtable[custID]->displayHistory();
}

Customer* History::searchCustomer(int cusID) {
	return customerHashtable[cusID];
}



