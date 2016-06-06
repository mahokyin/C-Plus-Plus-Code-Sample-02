//#include "transaction.h"
#include "inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory()
{

}

void Inventory::execute(MovieStore M, string singleLine)
{
	M.displayAllMovie();
}