#include "transaction.h"

using namespace std;

class Return : public Transaction 
{
public:
	// Default constructor
	Return();

	// implementation for return's execution
	virtual void execute(MovieStore, string);
};
