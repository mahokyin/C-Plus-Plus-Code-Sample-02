#include <iostream>
#include <string>
#include "classic.h"

using namespace std;

Classic::Classic(string d, string t, int y, string ty, string a, int m)
{
	director = d;                    //data for holding information about...
	title = t;                       //the different movies
	year = y;
	type = ty;
	actor = a;
	month = m;
}