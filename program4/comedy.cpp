// ----------------------------------------------- comedy.cpp ------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get comedys info with getter fnctions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "comedy.h"

using namespace std;

// -------------------------------Default Constructor-------------------------------------
Comedy::Comedy()
{
	// Empty constructor
}

// ------------------------------------Constructor---------------------------------------
// Description: Initializes the comedy movie information.
// PreCondition: Must get the movie director, title, year, type.
// PostCondition: Info will be saved in the comedy object.
// ---------------------------------------------------------------------------------------
Comedy::Comedy(string d, string t , int y, string ty)
{
	//Set the variables
	director = d;                    
	title = t;                       
	year = y;
	type = ty;
}

// ------------------------------------operator== ----------------------------------------
// Description: Compares a comedys titles.
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if comedy movies are ==
// ---------------------------------------------------------------------------------------
bool Comedy::operator==(const Movie &rhs) const
{
	if (rhs.getTitle() != this->getTitle()) return false;
	return true;
}

// ------------------------------------operator!= ----------------------------------------
// Description: Compares if the comedy movies are ==
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if comedy movies are !=
// ---------------------------------------------------------------------------------------
bool Comedy::operator!=(const Movie &rhs) const
{
	return !(rhs == *this);
}

// ------------------------------------operator< ----------------------------------------
// Description: Compares which comedy movie is <
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if comedy movies are <
// ---------------------------------------------------------------------------------------
bool Comedy::operator<(const Movie &rhs) const
{
	return (toupper(this->getTitle()[0]) < toupper((rhs.getTitle())[0]));
}

// ------------------------------------operator> ----------------------------------------
// Description: Compares which comedy movie is >
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if comedy movies are >
// ---------------------------------------------------------------------------------------
bool Comedy::operator>(const Movie &rhs) const
{
	return !(*this < rhs);
}

// -----------------------------------setDirector ----------------------------------------
// Description: Sets the director recieved into the comedys director variable
// PreCondition: Must get the director.
// PostCondition: New director is saved for this movie.
// ---------------------------------------------------------------------------------------
void Comedy::setDirector(string movieDiretor)
{
	this->director = movieDiretor;
}

// ---------------------------------setMovieTitle ----------------------------------------
// Description: Sets the movie title recieved into the comedys movie title variable
// PreCondition: Must get the movie title.
// PostCondition: New movie title is saved for this movie.
// ---------------------------------------------------------------------------------------
void Comedy::setMovieTitle(string movieTitle)
{
	this->title = movieTitle;
}

// ---------------------------------setMovieYear ----------------------------------------
// Description: Sets the movie year recieved into the comedys movie year variable
// PreCondition: Must get the movie year.
// PostCondition: New movie year is saved for this movie.
// ---------------------------------------------------------------------------------------
void Comedy::setMovieYear(int movieYear)
{
	this->year = movieYear;
}

// ---------------------------------setMovieGenre ----------------------------------------
// Description: Sets the movie genre recieved into the comedys movie genre variable
// PreCondition: Must get the movie genre.
// PostCondition: New movie genre is saved for this movie.
// ---------------------------------------------------------------------------------------
void Comedy::setMovieGenre(string movieGenre)
{
	this->type = movieGenre;
}