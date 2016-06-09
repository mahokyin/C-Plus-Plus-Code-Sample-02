#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>

using namespace std;

class Movie
{
public:
    Movie();
    //virtual ~Movie();                   //virtual destructor

    //pure virtual compare functions, must be implemented per inheriting class
    virtual bool operator==(const Movie &) const = 0;
    virtual bool operator!=(const Movie &) const = 0;
    virtual bool operator<(const Movie &) const = 0;
    virtual bool operator>(const Movie &) const = 0;

	virtual void setDirector(string movieDiretor) = 0;
	virtual void setMovieTitle(string movieTitle) = 0;
	virtual void setMovieYear(int movieYear) = 0;
	//virtual void setMovieGenre(string movieGenre) = 0;

    //functions to access the different data values per Movie object
    const string getDirector() const;
    virtual const string getTitle() const;
    const int getYear() const;
	const string getType() const;

protected:
    string director;                    //data for holding information about...
    string title;                       //the different movies
    int year;
    string type;                        //stores type of media (if expanding)...
};                                      //for now, will always be DVD

#endif
