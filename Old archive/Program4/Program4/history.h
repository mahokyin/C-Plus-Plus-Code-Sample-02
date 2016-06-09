#include "transaction.h"

using namespace std;

class History : public Transaction 
{
public:
	// Default constructor
	History();

	// implementation for History's execution
	virtual void execute(MovieStore, string);
};
