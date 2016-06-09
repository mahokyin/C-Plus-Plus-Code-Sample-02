#ifndef DRAMA_H
#define DRAMA_H
#include <iostream>
#include <string>
#include <iostream>
#include "movie.h"

class Drama :public Movie
{
public:
	Drama();
	Drama(string, string, int, string);
	//~Drama();
	virtual bool operator==(const Movie &) const;
	virtual bool operator!=(const Movie &) const;
	virtual bool operator<(const Movie &) const;
	virtual bool operator>(const Movie &) const;

	virtual void setDirector(string movieDiretor);
	virtual void setMovieTitle(string movieTitle);
	virtual void setMovieYear(int movieYear);
	virtual void setMovieGenre(string movieGenre);
};
#endif
