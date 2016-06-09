//#include "transaction.h"
#include "return.h"
#include <iostream>

using namespace std;

Return::Return(Inventory &inventory, History &history, int cusID, Movie &movie)
{
	/*
	// stock <= 0
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
	*/

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
			reason = "Invalid Action: Classic video does not exist !";
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

	// Check if customer are able to return
	if (customer == NULL) return;
	if (customer->canReturn("R", stockHashNode->movie, &reason)) {
		status = true;
	}
	else {
		status = false;
	}
}

void Return::execute() {
	if (!status) showError();
	else {
		customer->addTransacionHistory("R", stockHashNode->movie);
		stockHashNode->stock++;
		//cout << "Done !" << endl;
	}
}

void Return::showError() {
	if (customer != NULL)
		cout << customer->firstName << " " << customer->lastName << "(" << customer->customerID << ") : ";
	cout << reason << endl;
}


