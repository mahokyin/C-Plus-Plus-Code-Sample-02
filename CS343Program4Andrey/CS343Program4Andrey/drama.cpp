#include <iostream>
#include <string>
#include "drama.h"

using namespace std;

Drama::Drama(string d, string t, int y, string ty)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
}