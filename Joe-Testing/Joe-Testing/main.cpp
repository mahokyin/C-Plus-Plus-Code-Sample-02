#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include "customer.h"
using namespace std;

// Structure of hashtable and hashNode for Customer object
struct CustomerHashNode {
	Customer customer;
	CustomerHashNode *next;
};
CustomerHashNode *customerHashTable[10];
////////////////////////////////////////////////////////////

int hashCustomerID(int id) {
	string strID = to_string(id);
	return strID[0] - 48;
}

void addCustomer(Customer &customer) {
	int index = hashCustomerID(customer.customerID);
	if (customerHashTable[index] == NULL) {
		// if no collision
		CustomerHashNode *head = new CustomerHashNode;
		head->customer = customer;
		head->next = NULL;
		customerHashTable[index] = head;
	} else {
		// Solution of collision
		CustomerHashNode *newHead = new CustomerHashNode;
		newHead->customer = customer;
		newHead->next = customerHashTable[index];
		customerHashTable[index] = newHead;
	}
}

bool readCustomerData(ifstream &input) {
	string str;

	if (!input) return false;
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str)) {
		string id; string lastname; string firstname;
		istringstream(str) >> id >> lastname >> firstname;
		Customer customer(stoi(str), firstname, lastname);
		addCustomer(customer);
	}
	return true;
}

// Not sure yet.
void clearCustomer() {
	for (int i = 0; i < 10; i++) {
		CustomerHashNode *currentNode = customerHashTable[i];
		while (currentNode != NULL) {
			CustomerHashNode *oldPtr = currentNode;
			currentNode = currentNode->next;
			delete oldPtr; oldPtr = NULL;
		}
	}
}

// Not sure yet;
void clearCustomerTable() {
	clearCustomer();
	delete[] customerHashTable;
}

int main() {
	/*
	ifstream idTextFile("data4customers.txt");
	readCustomerData(idTextFile);

	CustomerHashNode *nodePtr;
	for (int i = 0; i < 10; i++) {
		nodePtr = customerHashTable[i];
		while (nodePtr != NULL) {
			cout << nodePtr->customer.customerID << " ";
			nodePtr = nodePtr->next;
		}
		cout << endl;
	}
	clearCustomerTable();
	*/
	
	system("pause");
	return 0;
}

