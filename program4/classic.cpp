// ----------------------------------------------- classic.cpp ---------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Used to add to get classic info with getter fnctions and operator overload. Child of Movie.
// ---------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "classic.h"

using namespace std;

// -------------------------------Default Constructor-------------------------------------
Classic::Classic()
{
	// Empty Consstructor
}

// ------------------------------------Constructor---------------------------------------
// Description: Initializes the classic movie information.
// PreCondition: Must get the movie director, title, year, type.
// PostCondition: Info will be saved in the classic object.
// ---------------------------------------------------------------------------------------
Classic::Classic(string d, string t, int y, string ty, string a, int da)
{
	//All of the movies info
	director = d;                    
	title = t;                      
	year = y;
	type = ty;
	actor = a;
	month = da;
}

// -----------------------------------getActor -------------------------------------------
// Description: Gets the actor name from this movie.
// PostCondition: Actor string is returned.
// ---------------------------------------------------------------------------------------
const string Classic::getActor() const
{
	return actor;
}

// -----------------------------------getMonth -------------------------------------------
// Description: Gets the month from this movie.
// PostCondition: month integer is returned.
// ---------------------------------------------------------------------------------------
const int Classic::getMonth() const
{
	return month;
}

// ------------------------------------operator== ----------------------------------------
// Description: Compares a classic titles.
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if classic movies are ==
// ---------------------------------------------------------------------------------------
bool Classic::operator==(const Movie &rhs) const
{	// Comparison for the year
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	if (this->year != rhsPtr->year) return false;
	else {
		return this->month == rhsPtr->month;
	}
}

// ------------------------------------operator!= ----------------------------------------
// Description: Compares if the classic movies are ==
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if classic movies are !=
// ---------------------------------------------------------------------------------------
bool Classic::operator!=(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return !(*this == *rhsPtr);
}

// ------------------------------------operator> ----------------------------------------
// Description: Compares which classic movie is >
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if classic movies are >
// ---------------------------------------------------------------------------------------
bool Classic::operator>(const Movie &rhs) const
{	// Comparison for the year
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	if (this->year > rhsPtr->year) return true;
	else if (this->year < rhsPtr->year) return false;
	else {
		return this->month > rhsPtr->month;
	}
}

// ------------------------------------operator< ----------------------------------------
// Description: Compares which classic movie is <
// PreCondition: Must get the movie.
// PostCondition: Now you can compare if classic movies are <
// ---------------------------------------------------------------------------------------
bool Classic::operator<(const Movie &rhs) const
{
	const Classic *rhsPtr = dynamic_cast<const Classic*>(&rhs);
	return !(*this > *rhsPtr);
}

// -----------------------------------setDirector ----------------------------------------
// Description: Sets the director recieved into the classic director variable
// PreCondition: Must get the director.
// PostCondition: New director is saved for this movie.
// ---------------------------------------------------------------------------------------
void Classic::setDirector(string movieDiretor)
{
	this->director = movieDiretor;
}

// ---------------------------------setMovieTitle ----------------------------------------
// Description: Sets the movie title recieved into the classic movie title variable
// PreCondition: Must get the movie title.
// PostCondition: New movie title is saved for this movie.
// ---------------------------------------------------------------------------------------
void Classic::setMovieTitle(string movieTitle)
{
	this->title = movieTitle;
}

// ---------------------------------setMovieYear ----------------------------------------
// Description: Sets the movie year recieved into the classic movie year variable
// PreCondition: Must get the movie year.
// PostCondition: New movie year is saved for this movie.
// ---------------------------------------------------------------------------------------
void Classic::setMovieYear(int movieYear)
{
	this->year = movieYear;
}

// ---------------------------------setMovieGenre ----------------------------------------
// Description: Sets the movie genre recieved into the classic movie genre variable
// PreCondition: Must get the movie genre.
// PostCondition: New movie genre is saved for this movie.
// ---------------------------------------------------------------------------------------
void Classic::setMovieGenre(string movieGenre)
{
	this->type = movieGenre;
}

// --------------------------------------setMonth ----------------------------------------
// Description: Sets the movie genre recieved into the classic movie genre variable
// PreCondition: Must get the movie genre.
// PostCondition: New movie genre is saved for this movie.
// ---------------------------------------------------------------------------------------
void Classic::setMonth(int movieMonth)
{
	this->month = movieMonth;
}