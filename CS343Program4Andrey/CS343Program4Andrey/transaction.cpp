#include "transaction.h"
#include "inventory.h"
#include "borrow.h"
#include "return.h"
#include "history.h"
#include <iostream>
#include <string>


using namespace std;

Transaction::Transaction()
{

}

Transaction *Transaction::genTrans(string singleLine)
{
	if (singleLine[0] == 'I')
		return new Inventory;
	else if (singleLine[0] == 'H')
		return new History;
	else if (singleLine[0] == 'B')
		return new Borrow;
	else if (singleLine[0] == 'R')
		return new Return;
}