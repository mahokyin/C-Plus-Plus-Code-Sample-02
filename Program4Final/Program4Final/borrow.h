#ifndef BORROW_H
#define BORROW_H
#include "transaction.h"

using namespace std;

class Borrow : public Transaction 
{
public:
	// Default constructor
	Borrow(Inventory &inventory, History &history, int cusID, Movie &movie);

	// implementation for borrow's execution
	virtual void execute();
	virtual void showError();
};

#endif