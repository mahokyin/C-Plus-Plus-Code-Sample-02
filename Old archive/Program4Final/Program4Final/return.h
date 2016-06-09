#ifndef RETURN_H
#define RETURN_H
#include "transaction.h"
//#include "transaction.cpp"
using namespace std;

class Return : public Transaction 
{
public:
	// Default constructor
	Return(Inventory &inventory, History &history, int cusID, Movie &movie);

	// implementation for return's execution
	virtual void execute();
	virtual void showError();
};

#endif