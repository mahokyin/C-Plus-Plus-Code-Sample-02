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

bool Classic::operator==(const Movie &) const
{
	return true;
}