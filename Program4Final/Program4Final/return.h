#ifndef RETURN_H
#define RETURN_H
#include "transaction.h"
using namespace std;

class Return : public Transaction 
{
public:
	// Default constructor
	Return();

	// implementation for return's execution
	virtual bool execute(Inventory, History, string);
	virtual void showError();
};

#endif