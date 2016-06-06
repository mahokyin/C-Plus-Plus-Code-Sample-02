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

protected:
};

#endif
