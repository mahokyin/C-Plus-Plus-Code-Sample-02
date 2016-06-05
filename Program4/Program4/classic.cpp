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
	/*if (this->director != rhsPtr->director) return false;
	if (this->title != rhsPtr->title) return false;
	if (this->year != rhsPtr->year) return false;
	if (this->type != rhsPtr->type) return false;
	if (this->actor != rhsPtr->actor) return false;*/
	if (this->day != rhsPtr->day) return false;
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
	return (this->day > rhsPtr->day);
}

bool Classic::operator<(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return (this->day < rhsPtr->day);
}