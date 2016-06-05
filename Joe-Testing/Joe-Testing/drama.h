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
};
#endif
