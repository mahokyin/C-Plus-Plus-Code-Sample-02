// ----------------------------------------------- drama.cpp -------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get drama info with getter functions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "drama.h"

// -------------------------------Default Constructor-------------------------------------
Drama::Drama()
{
	// Empty Constructor
}

// ------------------------------------Constructor---------------------------------------
// Description: Initializes the drama movie information.
// PreCondition: Must get the movie director, title, year, type.
// PostCondition: Info will be saved in the drama object.
// ---------------------------------------------------------------------------------------
Drama::Drama(string d, string t, int y, string ty)
{
	//All the data for a drama movie
	director = d;                    
	title = t;                      
	year = y;
	type = ty;
}

// ------------------------------------operator== ----------------------------------------
// Description: Compares a drama titles.
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if drama movies are ==
// ---------------------------------------------------------------------------------------
bool Drama::operator==(const Movie &rhs) const
{
	//compares directors
	return !(rhs.getDirector() != this->getDirector());
}

// ------------------------------------operator!= ----------------------------------------
// Description: Compares if the drama movies are ==
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if drama movies are !=
// ---------------------------------------------------------------------------------------
bool Drama::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}

// ------------------------------------operator< ----------------------------------------
// Description: Compares which drama movie is <
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if drama movies are <
// ---------------------------------------------------------------------------------------
bool Drama::operator<(const Movie &rhs) const
{
	return (toupper(rhs.getDirector()[0]) > toupper((this->getDirector())[0]));
}

// ------------------------------------operator> ----------------------------------------
// Description: Compares which drama movie is >
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if drama movies are >
// ---------------------------------------------------------------------------------------
bool Drama::operator>(const Movie &rhs) const
{
	return !(*this < rhs);
}

// -----------------------------------setDirector ----------------------------------------
// Description: Sets the director recieved into the drama director variable
// PreCondition: Must get the director.
// PostCondition: New director is saved for this movie.
// ---------------------------------------------------------------------------------------
void Drama::setDirector(string movieDiretor)
{
	this->director = movieDiretor;
}

// ---------------------------------setMovieTitle ----------------------------------------
// Description: Sets the movie title recieved into the drama movie title variable
// PreCondition: Must get the movie title.
// PostCondition: New movie title is saved for this movie.
// ---------------------------------------------------------------------------------------
void Drama::setMovieTitle(string movieTitle)
{
	this->title = movieTitle;
}

// ---------------------------------setMovieYear ----------------------------------------
// Description: Sets the movie year recieved into the drama movie year variable
// PreCondition: Must get the movie year.
// PostCondition: New movie year is saved for this movie.
// ---------------------------------------------------------------------------------------
void Drama::setMovieYear(int movieYear)
{
	this->year = movieYear;
}

