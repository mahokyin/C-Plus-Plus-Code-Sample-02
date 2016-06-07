//#include "transaction.h"
#include "history.h"
//#include "customer.h"
//#include "moviestore.h"
#include <iostream>

using namespace std;

History::History()
{

}

void History::execute(MovieStore M, string singleLine)
{
	int customerID;

	//Converts the string storing the customers ID into an integer
	customerID = (singleLine[2] - '0') * 1000;
	customerID += (singleLine[3] - '0') * 100;
	customerID += (singleLine[4] - '0') * 10;
	customerID += singleLine[5] - '0';

	M.displayCustomerHistory(customerID);
}