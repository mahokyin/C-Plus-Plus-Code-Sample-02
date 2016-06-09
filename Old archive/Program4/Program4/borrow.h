#ifndef BORROW_H
#define BORROW_H
#include "transaction.h"

using namespace std;

class Borrow : public Transaction 
{
public:
	// Default constructor
	Borrow();

	// implementation for borrow's execution
	virtual void execute(MovieStore, string);
};

#endif