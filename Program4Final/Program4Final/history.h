#include "customer.h"
using namespace std;

class History
{
public:
	// Default constructor
	History();
	bool addCustomer(Customer &customer); //adds a new customer into the hash array of customers
	void displayAllCustomerHistory();

private:
	// Structure of hashtable and hashNode for Customer object
	struct CustomerHashNode {
		Customer customer;
		CustomerHashNode *next = NULL;
	};
	CustomerHashNode *customerHashtable[10];
	int hashCustomerID(int id); // gets the hash value from the customer ID
	/*
	// Structure of hashtable and hashNode for Customer object
	struct HistoryData
	{
		string transactionType;  //Either borrowed or retuned
		Movie *movie = NULL;				 //All the info about the particular movie
		HistoryData *next = NULL;
	};
	HistoryData *historyHashtable[10000];
	Customer *customerHashtable[10000];

	struct IdRecordNode {
		int customerID;
		IdRecordNode *prev = NULL;
		IdRecordNode *next = NULL;
	};
	IdRecordNode *headIdNode = NULL;
	int hashCustomerID(int id); // gets the hash value from the customer ID
	void insertIdNode(int id);
	 */
};
