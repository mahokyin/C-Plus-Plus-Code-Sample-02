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
	bool operator==(const Comedy &) const;
	bool operator!=(const Comedy &) const;
	bool operator<(const Comedy &) const;
	bool operator>(const Comedy &) const;

protected:
};

#endif
