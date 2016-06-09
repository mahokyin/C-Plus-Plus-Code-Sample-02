// ------------------------------------------------ main.cpp -------------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// -----------------------------------------------------------------------------------------------------------------------
// Purpose - Main will take in the 3 files given and call MovieStore functions that will read the files and break them up.
// -----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "moviestore.h"
using namespace std;

int main() {
	//Saves files as ifstream and calls MovieStore constructor
	ifstream customerTextFile("data4customers.txt");
	ifstream movieTextFile("data4movies.txt");
	MovieStore movieStore(customerTextFile, movieTextFile);

	//Calls MovieStore function that reads and breaks the file up
	ifstream movieCommandFile("data4commands.txt");
	movieStore.readCommandData(movieCommandFile);

	return 0;
}