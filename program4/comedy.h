// ----------------------------------------------- comedy.h ------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get comedys info with getter fnctions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef COMEDY_H
#define COMEDY_H
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

class Comedy :public Movie
{
public:
	// -------------------------------Default Constructor-------------------------------------
	Comedy();

	// ------------------------------------Constructor---------------------------------------
	// Description: Initializes the comedy movie information.
	// PreCondition: Must get the movie director, title, year, type.
	// PostCondition: Info will be saved in the comedy object.
	// ---------------------------------------------------------------------------------------
	Comedy(string, string, int, string);

	// ------------------------------------operator== ----------------------------------------
	// Description: Compares a comedys titles.
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if comedy movies are ==
	// ---------------------------------------------------------------------------------------
	virtual bool operator==(const Movie &) const;

	// ------------------------------------operator!= ----------------------------------------
	// Description: Compares if the comedy movies are ==
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if comedy movies are !=
	// ---------------------------------------------------------------------------------------
	virtual bool operator!=(const Movie &) const;

	// ------------------------------------operator< ----------------------------------------
	// Description: Compares which comedy movie is <
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if comedy movies are <
	// ---------------------------------------------------------------------------------------
	virtual bool operator<(const Movie &) const;

	// ------------------------------------operator> ----------------------------------------
	// Description: Compares which comedy movie is >
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if comedy movies are >
	// ---------------------------------------------------------------------------------------
	virtual bool operator>(const Movie &) const;

	// -----------------------------------setDirector ----------------------------------------
	// Description: Sets the director recieved into the comedys director variable
	// PreCondition: Must get the director.
	// PostCondition: New director is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setDirector(string movieDiretor);

	// ---------------------------------setMovieTitle ----------------------------------------
	// Description: Sets the movie title recieved into the comedys movie title variable
	// PreCondition: Must get the movie title.
	// PostCondition: New movie title is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieTitle(string movieTitle);

	// ---------------------------------setMovieYear ----------------------------------------
	// Description: Sets the movie year recieved into the comedys movie year variable
	// PreCondition: Must get the movie year.
	// PostCondition: New movie year is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieYear(int movieYear);

	// ---------------------------------setMovieGenre ----------------------------------------
	// Description: Sets the movie genre recieved into the comedys movie genre variable
	// PreCondition: Must get the movie genre.
	// PostCondition: New movie genre is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieGenre(string movieGenre);
};

#endif
