// -------------------------------------------------- movie.h ----------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Parent function to Drama, Classic, and Comedy. Provides virtual functions for operators, getter functions
//			 and a setter function
// ---------------------------------------------------------------------------------------------------------------------
#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>

using namespace std;

class Movie
{
public:
	// ---------------------------------------Constructor-------------------------------------
	// Description: Initialize the member variables
	// ---------------------------------------------------------------------------------------
    Movie();
    
    //pure virtual compare functions, must be implemented per inheriting class
    virtual bool operator==(const Movie &) const = 0;
    virtual bool operator!=(const Movie &) const = 0;
    virtual bool operator<(const Movie &) const = 0;
    virtual bool operator>(const Movie &) const = 0;

	virtual void setDirector(string movieDiretor) = 0;
	virtual void setMovieTitle(string movieTitle) = 0;
	virtual void setMovieYear(int movieYear) = 0;
	
    //functions to access the different data values per Movie object
    const string getDirector() const;
    virtual const string getTitle() const;
    const int getYear() const;

protected:
    string director;                    //data for holding information about...
    string title;                       //the different movie names, director, and year
    int year;
    string type;                        //stores type of media (if expanding)...
};                                      //for now, will always be DVD

#endif
