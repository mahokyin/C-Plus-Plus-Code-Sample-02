#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "moviestore.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Transaction 
{
public:
	// abstract function (Borrow and Return class have different process)
	virtual void execute(MovieStore, string) = 0;
};

#endif