#include <iostream>
#include <string>
#include "comedy.h"

using namespace std;

Comedy::Comedy()
{
	// Empty constructor
}

Comedy::Comedy(string d, string t , int y, string ty)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
}

bool Comedy::operator==(const Movie &rhs) const
{
	if (rhs.getTitle() != this->getTitle()) return false;
	return true;
}

bool Comedy::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}

bool Comedy::operator<(const Movie &rhs) const
{
	return (toupper(this->getTitle()[1]) < toupper((rhs.getTitle())[1]));
}

bool Comedy::operator>(const Movie &rhs) const
{
	return !(*this < rhs);
}