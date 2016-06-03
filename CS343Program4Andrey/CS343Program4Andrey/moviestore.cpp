#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include "moviestore.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

//#include "customer.h"

using namespace std;


MovieStore::MovieStore()
{
	head->nextGenre = new movieHead;
	head->nextGenre->genre = "classic";
	head->nextGenre->nextGenre = new movieHead;
	head->nextGenre->nextGenre->genre = "comedy";
	head->nextGenre->nextGenre->nextGenre = new movieHead;
	head->nextGenre->nextGenre->nextGenre->genre = "drama";
	head->nextGenre->nextGenre->nextGenre->nextGenre = NULL;
}


void MovieStore::readMovieData(ifstream &movieTextFile)
{
	string genre; //genre
	int stockAmount = 0; //stock
	string movieName;
	string director;
	int movieYear;
	int movieDay;
	string firstName;
	string lastName;

	//ifstream movieTextFile("data4movies.txt");
	if (!movieTextFile) cout << "movie error" << endl;

	while (!movieTextFile.eof())
	{
		movieTextFile >> genre;
		genre = genre[0];

		if (genre == "F" || genre == "D")
		{
			movieTextFile.get();
			movieTextFile >> stockAmount;

			movieTextFile.get();
			getline(movieTextFile, director, ',');

			movieTextFile.get();
			getline(movieTextFile, movieName, ',');

			movieTextFile.get();
			movieTextFile >> movieYear;

			//cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |Year|: " << movieYear << endl;

			if (genre == "F")
			{
				Comedy *newMovieF = new Comedy(director, movieName, movieYear, genre);
				addMovie(newMovieF, stockAmount);
			}
			else
			{
				Drama *newMovieD = new Drama(director, movieName, movieYear, genre);
				addMovie(newMovieD, stockAmount);
			}
		}
		else if (genre == "C" || genre == "Z")
		{
			movieTextFile.get();
			movieTextFile >> stockAmount;

			movieTextFile.get();
			getline(movieTextFile, director, ',');

			movieTextFile.get();
			getline(movieTextFile, movieName, ',');

			movieTextFile.get();
			movieTextFile >> firstName;

			movieTextFile.get();
			movieTextFile >> lastName;

			movieTextFile.get();
			movieTextFile >> movieDay;

			movieTextFile.get();
			movieTextFile >> movieYear;

			if (genre == "C")
			{
				Classic *newMovieC = new Classic(director, movieName, movieYear, genre, firstName + lastName, movieDay);
				addMovie(newMovieC, stockAmount);
			}

			//cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |First|: " << firstName << " |Second|: " << lastName << " |Day|: " << movieDay << " |Year|: " << movieYear << endl;
		}
	}	 
}

void MovieStore::addMovie(Movie *newMovie, int stockAmount)
{
	movieHead *curr = head;

	if (Classic *classic = dynamic_cast<Classic*>(newMovie))
	{
		while (curr->nextGenre != NULL)
		{
			if (curr->genre == "classic")
			{
				if(curr->first == NULL)
				{
					curr->first = new movieNode;
					curr->first->maxStock = stockAmount;
					curr->first->stock = stockAmount;
					curr->first->next = NULL;
					curr->first->m = classic;
				}
			}
		}
	}
	else if (Drama *drama = dynamic_cast<Drama*>(newMovie))
	{

	}
	else if (Comedy *comedy = dynamic_cast<Comedy*>(newMovie))
	{

	}

}