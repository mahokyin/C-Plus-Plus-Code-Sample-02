// ------------------------------------------------ transaction.h ------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Parent class of return and borrow, pure virtual execute and showError functions. Stores all the member 
//			 variables needed for borrow and return.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "inventory.h"
#include "history.h"

class Transaction 
{
public:
	//Pure virtual functions that are implimented in Borrow and Return
	virtual void execute() = 0;
	virtual void showError() = 0;

protected:
	//Member variables, used by Borrow and Return
	string reason;
	bool status;
	Inventory *inventory = NULL;
	History *history = NULL;
	Customer *customer = NULL;
	MovieHashNode *stockHashNode = NULL;
};

#endif