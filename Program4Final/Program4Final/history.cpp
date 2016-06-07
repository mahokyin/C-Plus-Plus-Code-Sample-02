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

bool History::addCustomer(Customer &customer) {
	if (customerHashtable[customer.customerID] == NULL) {
		customerHashtable[customer.customerID] = &customer;
		return true;
	}
	else {
		cout << "Invalid Customer ID" << endl;
	}
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


void History::displayAllCustomerHistory() {
	cout << "ID" << setw(23) << "Frist name" << setw(23) << "Last name \n";
	for (int i = 0; i < 10000; i++) {
		Customer *customer = customerHashtable[i];
		if (customerHashtable[i] != NULL) {
			cout << customer->customerID << setw(20) << customer->firstName << setw(20) << customer->lastName << endl;
		}
	}
	cout << endl;
}

void History::displayCustomerHistory(int custID)
{
	customerHashtable[custID]->displayHistory();
}