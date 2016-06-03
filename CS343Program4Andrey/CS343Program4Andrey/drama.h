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
	~Drama();
	bool operator==(const Movie &);
	bool operator!=(const Movie &);
	bool operator<(const Movie &);
	bool operator>(const Movie &);

protected:
};

#endif
