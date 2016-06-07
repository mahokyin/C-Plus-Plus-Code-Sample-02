#ifndef BORROW_H
#define BORROW_H
#include "transaction.h"

using namespace std;

class Borrow : public Transaction 
{
public:
	// Default constructor
	Borrow(/*int cusID, string type, Movie movie*/);

	// implementation for borrow's execution
	virtual bool execute(Inventory, History, string);
	virtual void showError();
};

#endif