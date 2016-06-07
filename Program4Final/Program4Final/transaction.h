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
	// abstract function (Borrow and Return class have different process)
	virtual bool execute(Inventory, History, string) = 0;
	virtual void showError() = 0;
};

#endif