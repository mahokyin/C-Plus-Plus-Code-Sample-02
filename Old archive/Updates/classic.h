#ifndef CLASSIC_H
#define CLASSIC_H
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

class Classic :public Movie
{
public:
	Classic();
	Classic(string, string, int, string, string, int);
	~Classic();
	bool operator==(const Movie &);
	bool operator!=(const Movie &);
	bool operator<(const Movie &);
	bool operator>(const Movie &);

	const string getActor() const;      //gets the actor string for classics
	const int getDay() const;         //gets the month int for classics

	virtual void setDirector(string movieDiretor);
	virtual void setMovieTitle(string movieTitle);
	virtual void setMovieYear(int movieYear);
	virtual void setMovieGenre(string movieGenre);
	//void setActor(string actorName);
	void setMonth(int movieMonth);

protected:
	string actor;                       //used to contain the extra actor...
	int day;                          //info in classic movies
};

#endif
