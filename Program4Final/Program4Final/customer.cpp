#include "customer.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

Customer::Customer() {
	customerID = 0;
	firstName = "N/A";
	lastName = "N/A";
	//head = new HistoryData;
	head = NULL;
}

Customer::Customer(int id, string firstname, string lastname) {
	this->customerID = id;
	this->firstName = firstname;
	this->lastName = lastname;
	//head = new HistoryData;
	head = NULL;
}

Customer::~Customer() {
	// Delete linkedlist ptrs
	while (head != NULL) {
		HistoryData *oldNode = head;
		head = head->next;
		delete oldNode;
		oldNode = NULL;
	}
}

void Customer::addTransacionHistory(string trans, Movie *movie)
{
	HistoryData *newHistory = new HistoryData;
	newHistory->movie = movie;
	newHistory->transactionType = trans;
	newHistory->next = head;
	head = newHistory;
}

void Customer::displayHistory()
{
	//cout << internal << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(20) << "Actor" << setw(22) << "Month" << setw(18) << "Year" << endl;

	if (head == NULL) {
		cout << "No transaction history of " << this->firstName << " " << this->lastName << " (" << this->customerID << ")" << endl;
		return;
	}

	cout << endl;
	cout << "Transaction history of " << this->firstName << " " << this->lastName << " (" << this->customerID << ")" << endl;
	HistoryData *curr = head;
	while (curr != NULL)
	{
		cout << curr->transactionType << " ";

		Classic *classic = dynamic_cast<Classic*>(curr->movie);

		//Check the genre of the movie
		if (classic == NULL)
		{
			//Print out drama's and comedy's information
			cout << curr->movie->getTitle() << " " << curr->movie->getDirector() << " " << curr->movie->getYear() << endl;
		}
		else
		{
			//Print out classics information
			cout << classic->getTitle() << " " << classic->getDirector() << " " << classic->getYear() << " " << classic->getMonth() << " " << classic->getActor() << endl;
		}

		curr = curr->next; //Traverse the linked list
	}
}


bool Customer::canBorrow(string transType, Movie *movie) {
	if (head == NULL) return true;
	HistoryData *currPtr = head;
	while (currPtr != NULL) {
		if (currPtr->transactionType == transType && currPtr->movie == movie) return false;
		if (currPtr->transactionType != transType && currPtr->movie == movie) return true;
		currPtr = currPtr->next;
	}
	return true;
}

bool Customer::canReturn(string transType, Movie *movie, string *errorMsg) {
	if (head == NULL) return false;
	HistoryData *currPtr = head;
	while (currPtr != NULL) {
		if (currPtr->transactionType == transType && currPtr->movie == movie) {
			*errorMsg = "Customer didn't return the same item";
			return false;
		}
		if (currPtr->transactionType != transType && currPtr->movie == movie) return true;
		currPtr = currPtr->next;
	}
	*errorMsg = "Customer didn't borrow this item before";
	return false;
}