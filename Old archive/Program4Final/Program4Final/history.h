#include "customer.h"
using namespace std;

class History
{
public:
	// Default constructor
	History();
	~History();
	bool addCustomer(Customer *customer); //adds a new customer into the hash array of customers
	void displayCustomerHistory(int custID);
	Customer* searchCustomer(int cusID);

private:
	Customer *customerHashtable[10000];
};
