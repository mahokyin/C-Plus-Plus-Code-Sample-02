// ----------------------------------------------- classic.h ------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get classic info with getter fnctions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#ifndef CLASSIC_H
#define CLASSIC_H
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;

class Classic :public Movie
{
public:
	// -------------------------------Default Constructor-------------------------------------
	Classic();

	// ------------------------------------Constructor---------------------------------------
	// Description: Initializes the classic movie information.
	// PreCondition: Must get the movie director, title, year, type.
	// PostCondition: Info will be saved in the classic object.
	// ---------------------------------------------------------------------------------------
	Classic(string, string, int, string, string, int);

	// ------------------------------------operator== ----------------------------------------
	// Description: Compares a classic titles.
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if classic movies are ==
	// ---------------------------------------------------------------------------------------
	virtual bool operator==(const Movie &) const;

	// ------------------------------------operator!= ----------------------------------------
	// Description: Compares if the classic movies are ==
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if classic movies are !=
	// ---------------------------------------------------------------------------------------
	virtual bool operator!=(const Movie &) const;

	// ------------------------------------operator< ----------------------------------------
	// Description: Compares which classic movie is <
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if classic movies are <
	// ---------------------------------------------------------------------------------------
	virtual bool operator<(const Movie &) const;

	// ------------------------------------operator> ----------------------------------------
	// Description: Compares which classic movie is >
	// PreCondition: Must get the movie.
	// PostCondition: Now you can compare if classic movies are >
	// ---------------------------------------------------------------------------------------
	virtual bool operator>(const Movie &) const;

	// -----------------------------------getActor -------------------------------------------
	// Description: Gets the actor name from this movie.
	// PostCondition: Actor string is returned.
	// ---------------------------------------------------------------------------------------
	const string getActor() const;      

	// -----------------------------------getMonth -------------------------------------------
	// Description: Gets the month from this movie.
	// PostCondition: month integer is returned.
	// ---------------------------------------------------------------------------------------
	const int getMonth() const;       

	// -----------------------------------setDirector ----------------------------------------
	// Description: Sets the director recieved into the classic director variable
	// PreCondition: Must get the director.
	// PostCondition: New director is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setDirector(string movieDiretor);

	// ---------------------------------setMovieTitle ----------------------------------------
	// Description: Sets the movie title recieved into the classic movie title variable
	// PreCondition: Must get the movie title.
	// PostCondition: New movie title is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieTitle(string movieTitle);

	// ---------------------------------setMovieYear ----------------------------------------
	// Description: Sets the movie year recieved into the classic movie year variable
	// PreCondition: Must get the movie year.
	// PostCondition: New movie year is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieYear(int movieYear);

	// ---------------------------------setMovieGenre ----------------------------------------
	// Description: Sets the movie genre recieved into the classic movie genre variable
	// PreCondition: Must get the movie genre.
	// PostCondition: New movie genre is saved for this movie.
	// ---------------------------------------------------------------------------------------
	virtual void setMovieGenre(string movieGenre);

	// --------------------------------------setMonth ----------------------------------------
	// Description: Sets the movie genre recieved into the classic movie genre variable
	// PreCondition: Must get the movie genre.
	// PostCondition: New movie genre is saved for this movie.
	// ---------------------------------------------------------------------------------------
	void setMonth(int movieMonth);
protected:
	string actor;   //actor
	int month;      //month of movie
};

#endif
