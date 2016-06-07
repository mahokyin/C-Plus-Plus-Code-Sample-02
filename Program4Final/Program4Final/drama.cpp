#include <iostream>
#include <string>
#include "drama.h"

Drama::Drama()
{
	// Empty Constructor
}
Drama::Drama(string d, string t, int y, string ty)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
}

bool Drama::operator==(const Movie &rhs) const
{
	if (rhs.getDirector() != this->getDirector()) return false;
	return true;
}

bool Drama::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}

bool Drama::operator<(const Movie &rhs) const
{
	return (toupper(rhs.getDirector()[0]) > toupper((this->getDirector())[0]));
}

bool Drama::operator>(const Movie &rhs) const
{
	return !(*this < rhs);
}

void Drama::setDirector(string movieDiretor)
{
	this->director = movieDiretor;
}


void Drama::setMovieTitle(string movieTitle)
{
	this->title = movieTitle;
}


void Drama::setMovieYear(int movieYear)
{
	this->year = movieYear;
}


void Drama::setMovieGenre(string movieGenre)
{
	this->type = movieGenre;
}