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
	virtual void execute() = 0;
	virtual void showError() = 0;

protected:
	string reason;
	bool status;
	Inventory *inventory = NULL;
	History *history = NULL;
	Customer *customer = NULL;
	MovieHashNode *stockHashNode = NULL;
};

#endif