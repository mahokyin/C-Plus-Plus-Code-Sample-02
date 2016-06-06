//#include "transaction.h"
#include "borrow.h"
#include <iostream>

using namespace std;

Borrow::Borrow()
{

}

void Borrow::execute(MovieStore M, string singleLine)
{
	M.borrowMovie(singleLine);
}