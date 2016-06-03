#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

Movie::Movie()
{

}

const string Movie::getDirector() const
{
	return director;
}

const string Movie::getTitle() const
{
	return title;
}

const int Movie::getYear() const
{
	return year;
}