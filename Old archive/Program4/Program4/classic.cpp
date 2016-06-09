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
	month = da;
}

const string Classic::getActor() const
{
	return actor;
}

const int Classic::getMonth() const
{
	return month;
}

bool Classic::operator==(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	if (this->year != rhsPtr->year) return false;
	else {
		if (this->month == rhsPtr->month) return true;
		else return false;
	}
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
		if (this->month > rhsPtr->month) return true;
		else return false;
	}
	
}

bool Classic::operator<(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return !(*this > *rhsPtr);
}

void Classic::setDirector(string movieDiretor)
{
	this->director = movieDiretor;
}


void Classic::setMovieTitle(string movieTitle)
{
	this->title = movieTitle;
}


void Classic::setMovieYear(int movieYear)
{
	this->year = movieYear;
}


void Classic::setMovieGenre(string movieGenre)
{
	this->type = movieGenre;
}

//void Classic::setActor(string actorName)
//{
//	this->actor = actorName;
//}

void Classic::setMonth(int movieMonth)
{
	this->month = movieMonth;
}