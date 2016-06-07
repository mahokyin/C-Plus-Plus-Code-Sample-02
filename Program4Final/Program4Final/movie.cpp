#include "movie.h"
using namespace std;

Movie::Movie() {
	director = "N/A";
	title = "N/A";
	year = 0;
	type = "N/A";
}

const string Movie::getDirector() const {
	return director;
}

const string Movie::getTitle() const {
	return title;
}

const int Movie::getYear() const {
	return year;
}