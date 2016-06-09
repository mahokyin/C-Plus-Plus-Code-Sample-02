#ifndef COMEDY_H
#define COMEDY_H
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

class Comedy :public Movie
{
public:
	Comedy();
	Comedy(string, string, int, string);
	~Comedy();
	virtual bool operator==(const Movie &) const;
	virtual bool operator!=(const Movie &) const;
	virtual bool operator<(const Movie &) const;
	virtual bool operator>(const Movie &) const;

	virtual void setDirector(string movieDiretor);
	virtual void setMovieTitle(string movieTitle);
	virtual void setMovieYear(int movieYear);
	virtual void setMovieGenre(string movieGenre);

protected:
};

#endif
