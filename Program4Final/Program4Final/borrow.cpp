#include "borrow.h"
#include <iostream>

using namespace std;

Borrow::Borrow(Inventory &inventory, History &history, int cusID, Movie &movie) {
	this->inventory = &inventory;
	this->history = &history;

	stockHashNode = this->inventory->searchInventory(&movie);
	// Check if this is existing first
	if (stockHashNode == NULL) {
		status = false;
		if (Classic *obj = dynamic_cast<Classic*>(&movie)) {
			reason = "Invalid Action: Classic video does not exist !";
		}
		else if (Drama *obj = dynamic_cast<Drama*>(&movie)) {
			reason = "Invalid Action: Drama video does not exist !";
		}
		else {
			reason = "Invalid Action: Comedy video does not exist !";
		}
		return;
	}

	// stock <= 0
	if (stockHashNode == NULL) return;
	if (stockHashNode->stock <= 0) {
		status = false;
		if (Classic *obj = dynamic_cast<Classic*>(&movie)) {
			reason = "Invalid Action: There is no more classic video !";
		}
		else if (Drama *obj = dynamic_cast<Drama*>(&movie)) {
			reason = "Invalid Action: There is no more dramma video !";
		}
		else {
			reason = "Invalid Action: There is no more Classic video !";
		}
		return;
	}

	// Check if customer exist
	customer = history.searchCustomer(cusID);
	if (customer == NULL) {
		status = false;
		reason = "Invalid Action: invalid customer ID !";
		return;
	}
	
	// Check if customer are able to borrow
	if (customer == NULL) return;
	if (customer->canBorrow("B", stockHashNode->movie)) {
		status = true;
	}
	else {
		status = false;
		reason = "Customer can't borrow the same item !";
	}
}

void Borrow::execute() {
	if (!status) showError();
	else {
		cout << "Done " << endl;
		customer->addTransacionHistory("B", stockHashNode->movie);
		stockHashNode->stock--;
	}
}

void Borrow::showError() {
	if (customer != NULL)
		cout << customer->firstName << " " << customer->lastName << "(" << customer->customerID << ") : ";
	cout << reason << endl;
}