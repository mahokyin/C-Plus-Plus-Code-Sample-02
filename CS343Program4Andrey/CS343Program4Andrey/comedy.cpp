#include <iostream>
#include <string>
#include "comedy.h"

using namespace std;

Comedy::Comedy(string d, string t , int y, string ty)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
}

bool Comedy::operator==(const Movie &rhs)
{
	if (rhs.getTitle() == this->getTitle())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//bool operator!=(const Movie &);
//bool operator<(const Movie &);
//bool operator>(const Movie &);