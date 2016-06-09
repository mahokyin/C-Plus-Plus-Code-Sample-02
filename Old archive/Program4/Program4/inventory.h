#include "transaction.h"

using namespace std;

class Inventory : public Transaction 
{
public:
	// Default constructor
	Inventory();

	// implementation for inventory's execution
	virtual void execute(MovieStore, string);
};
