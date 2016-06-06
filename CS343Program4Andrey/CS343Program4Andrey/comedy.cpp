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
/*
bool Comedy::operator==(const Movie &rhs) const
{
	Comedy rhs = dynamic_cast<Classic*>(rhs);

	if (rhs.getTitle() != this->getTitle()) return false;
	if (rhs.getDirector() != this->getDirector()) return false;
	if (rhs.getYear() != this->getYear()) return false;

	return true;
}*/

bool Comedy::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}

bool Comedy::operator<(const Movie &rhs) const
{
	if ((rhs.getTitle())[0] < (this->getTitle())[0]) return false;

	return true;
}

bool Comedy::operator>(const Movie &rhs) const
{
	return (rhs < *this);
}