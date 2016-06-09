#ifndef DRAMA_H
#define DRAMA_H
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

class Drama :public Movie
{
public:
	Drama();
	Drama(string, string, int, string);
	~Drama();
	bool operator==(const Movie &);
	bool operator!=(const Movie &);
	bool operator<(const Movie &);
	bool operator>(const Movie &);

	virtual void setDirector(string movieDiretor);
	virtual void setMovieTitle(string movieTitle);
	virtual void setMovieYear(int movieYear);
	virtual void setMovieGenre(string movieGenre);

protected:
};

#endif
