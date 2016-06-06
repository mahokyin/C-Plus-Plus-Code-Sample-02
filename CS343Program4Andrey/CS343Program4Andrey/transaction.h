#include "moviestore.h"

class Transaction 
{
public:
	// Default constructor
	Transaction();

	// static factory function to return a object belonging child class
	static Transaction *genTrans(string);

	// abstract function (Borrow and Return class have different process)
	virtual void execute(MovieStore, string) = 0;
};
