#include "customer.h"
using namespace std;

class History
{
public:
	// Default constructor
	History();
	bool addCustomer(Customer &customer); //adds a new customer into the hash array of customers
	bool addCustomer(Customer *customer); //adds a new customer into the hash array of customers
	void displayAllCustomerHistory();
	void displayCustomerHistory(int custID);

private:
	Customer *customerHashtable[10000];
};
