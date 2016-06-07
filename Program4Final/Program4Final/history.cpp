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
	for (int i = 0; i < 10; i++) {
		customerHashtable[i] = NULL;
	}
	cout << "Initilize the customerHashtable successfully !" << endl;
}

/*
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
 */

int History::hashCustomerID(int id) {
	ostringstream ss; ss << id;
	string strID = ss.str();
	return strID[0] - 48;
}

bool History::addCustomer(Customer &customer) {
	int index = hashCustomerID(customer.customerID);
	if (customerHashtable[index] == NULL) {
		// if no collision
		CustomerHashNode *head = new CustomerHashNode;
		head->customer = customer;
		head->next = NULL;
		customerHashtable[index] = head;
		return true;
	}
	else {
		// Solution of collision
		CustomerHashNode *newHead = new CustomerHashNode;
		newHead->customer = customer;
		newHead->next = customerHashtable[index];
		customerHashtable[index] = newHead;
		return true;
	}
}

void History::displayAllCustomerHistory() {
	cout << "ID" << setw(23) << "Frist name" << setw(23) << "Last name \n";
	CustomerHashNode *nodePtr;
	for (int i = 0; i < 10; i++) {
		nodePtr = customerHashtable[i];
		while (nodePtr != NULL) {
			cout << nodePtr->customer.customerID << setw(20) << nodePtr->customer.firstName << setw(20) << nodePtr->customer.lastName << endl;
			nodePtr = nodePtr->next;
		}
	}
	cout << endl;
}

/*
void History::insertIdNode(int id) {
	if (headIdNode != NULL) {
		IdRecordNode *newIdRecord = new IdRecordNode;
		newIdRecord->customerID = id;
		newIdRecord->prev = NULL;
		newIdRecord->next = headIdNode;
		headIdNode->prev = newIdRecord;
		headIdNode = newIdRecord;
	} else {
		headIdNode = new IdRecordNode;
		headIdNode->customerID = id;
		headIdNode->prev = NULL;
		headIdNode->next = NULL;
	}
}
*/
