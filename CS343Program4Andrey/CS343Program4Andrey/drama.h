// ----------------------------------------------- drama.h -------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get drama info with getter functions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef DRAMA_H
#define DRAMA_H
#include <iostream>
#include <string>
#include <iostream>
#include "movie.h"

class Drama :public Movie
{
public:
	// -------------------------------Default Constructor-------------------------------------
	Drama();

	// ------------------------------------Constructor---------------------------------------
	// Description: Initializes the drama movie information.
	// PreCondition: Must get the movie director, title, year, type.
	// PostCondition: Info will be saved in the drama object.
	// ---------------------------------------------------------------------------------------
	Drama(string, string, int, string);
	
	// ------------------------------------operator== ----------------------------------------
	// Description: Compares a drama titles.
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if drama movies are ==
	// ---------------------------------------------------------------------------------------
	virtual bool operator==(const Movie &) const;

	// ------------------------------------operator!= ----------------------------------------
	// Description: Compares if the drama movies are ==
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if drama movies are !=
	// ---------------------------------------------------------------------------------------
	virtual bool operator!=(const Movie &) const;

	// ------------------------------------operator< ----------------------------------------
	// Description: Compares which drama movie is <
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if drama movies are <
	// ---------------------------------------------------------------------------------------
	virtual bool operator<(const Movie &) const;

	// ------------------------------------operator> ----------------------------------------
	// Description: Compares which drama movie is >
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if drama movies are >
	// ---------------------------------------------------------------------------------------
	virtual bool operator>(const Movie &) const;

	// -----------------------------------setDirector ----------------------------------------
	// Description: Sets the director recieved into the drama director variable
	// PreCondition: Must get the director.
	// PostCondition: New director is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setDirector(string movieDiretor);

	// ---------------------------------setMovieTitle ----------------------------------------
	// Description: Sets the movie title recieved into the drama movie title variable
	// PreCondition: Must get the movie title.
	// PostCondition: New movie title is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieTitle(string movieTitle);

	// ---------------------------------setMovieYear ----------------------------------------
	// Description: Sets the movie year recieved into the drama movie year variable
	// PreCondition: Must get the movie year.
	// PostCondition: New movie year is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieYear(int movieYear);

	// ---------------------------------setMovieGenre ----------------------------------------
	// Description: Sets the movie genre recieved into the drama movie genre variable
	// PreCondition: Must get the movie genre.
	// PostCondition: New movie genre is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieGenre(string movieGenre);
};
#endif
