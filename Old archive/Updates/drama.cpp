#include <iostream>
#include <string>
#include "drama.h"

using namespace std;

Drama::Drama(string d, string t, int y, string ty)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
}

//////////////////////////////////////////////////////////////////////////NEW
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