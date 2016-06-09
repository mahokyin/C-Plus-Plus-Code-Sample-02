// -------------------------------------------------- movie.cpp --------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - Parent function to Drama, Classic, and Comedy. Provides virtual functions for operators, getter functions
//			 and a setter function
// ---------------------------------------------------------------------------------------------------------------------
#include "movie.h"

using namespace std;

// ---------------------------------------Constructor-------------------------------------
// Description: Initialize the member variables
// ---------------------------------------------------------------------------------------
Movie::Movie() {
	director = "N/A";
	title = "N/A";
	year = 0;
	type = "N/A";
}

//Getter functions: return the member variable that are desired
const string Movie::getDirector() const {
	return director;
}

const string Movie::getTitle() const {
	return title;
}

const int Movie::getYear() const {
	return year;
}