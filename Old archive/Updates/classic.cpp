#include <iostream>
#include <string>
#include "classic.h"

using namespace std;

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

//////////////////////////////////////////////////////////////////////////NEW
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
	this->day = movieMonth;
}