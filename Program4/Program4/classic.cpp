#include <iostream>
#include <string>
#include "classic.h"

using namespace std;

Classic::Classic()
{
	// Empty Consstructor
}

Classic::Classic(string d, string t, int y, string ty, string a, int da)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
	actor = a;
	day = da;
}

const string Classic::getActor() const
{
	return actor;
}

const int Classic::getDay() const
{
	return day;
}

bool Classic::operator==(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	if (this->year != rhsPtr->day) return false;
	else {
		if (this->day == rhsPtr->day) return true;
		else return false;
	}
	return true;
}

bool Classic::operator!=(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return !(*this == *rhsPtr);
}

// Comparison for the year
bool Classic::operator>(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	if (this->year > rhsPtr->year) return true;
	else if (this->year < rhsPtr->year) return false;
	else {
		if (this->day > rhsPtr->day) return true;
		else return false;
	}
	
}

bool Classic::operator<(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return !(*this > *rhsPtr);
}