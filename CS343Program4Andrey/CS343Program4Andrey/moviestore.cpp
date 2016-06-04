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

	while (curr->nextGenre != NULL)
	{
		if (Classic *classic = dynamic_cast<Classic*>(newMovie))
		{
			if (curr->genre == "classic")
			{
				Classic *c = dynamic_cast<Classic*>(curr->first->m);

				if (curr->first == NULL)
				{
					curr->first = new movieNode;
					curr->first->maxStock = stockAmount;
					curr->first->stock = stockAmount;
					curr->first->next = NULL;
					c = classic;
				}
				else 
				{
					movieNode *currMovieNode = curr->first;
					c = dynamic_cast<Classic*>(currMovieNode->m);

					movieNode *prevMovieNode = NULL;
					Classic *prevC = NULL;
					while (currMovieNode != NULL)
					{
						if (c->getDay() == classic->getDay())
						{
							if (classic->getActor()[0] == c->getActor()[0])
							{
								prevMovieNode = currMovieNode;
								prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
								if (currMovieNode == NULL)
								{
									prevMovieNode->next = new movieNode;
									prevMovieNode->next->m = classic;
									prevMovieNode->next->maxStock = stockAmount;
									prevMovieNode->next->stock = stockAmount;
									prevMovieNode->next->next = NULL;
									break;
								}
							}
							else if (classic->getActor()[0] < c->getActor()[0])
							{
								prevMovieNode->next = new movieNode;
								prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = currMovieNode;
								break;
							}
							else if (classic->getActor()[0] > c->getActor()[0])
							{
								prevMovieNode = currMovieNode;
								prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
							}
						} 
						else if (classic->getDay() > c->getDay())
						{
							prevMovieNode = currMovieNode;
							prevC = dynamic_cast<Classic*>(currMovieNode->m);
							currMovieNode = currMovieNode->next;
							if (currMovieNode == NULL) 
							{
								prevMovieNode->next = new movieNode;
								prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = NULL;
								break;
							}
						}
						else if (classic->getDay() < c->getDay())
						{
							prevMovieNode->next = new movieNode;
							prevMovieNode->next->m = classic;
							prevMovieNode->next->maxStock = stockAmount;
							prevMovieNode->next->stock = stockAmount;
							prevMovieNode->next->next = currMovieNode;
							break;
						}
					}
				}
			}
		}
		else if (Drama *drama = dynamic_cast<Drama*>(newMovie))
		{/*
			if (curr->genre == "drama")
			{
				Drama *c = dynamic_cast<Drama*>(curr->first->m);

				if (curr->first == NULL)
				{
					curr->first = new movieNode;
					curr->first->maxStock = stockAmount;
					curr->first->stock = stockAmount;
					curr->first->next = NULL;
					c = drama;
				}
				else
				{
					movieNode *currMovieNode = curr->first;
					c = dynamic_cast<Classic*>(currMovieNode->m);

					movieNode *prevMovieNode = NULL;
					Classic *prevC = NULL;
					while (currMovieNode != NULL)
					{
						if (c->getDay() == classic->getDay())
						{
							if (classic->getActor()[0] == c->getActor()[0])
							{
								prevMovieNode = currMovieNode;
								prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
								if (currMovieNode == NULL)
								{
									prevMovieNode->next = new movieNode;
									prevMovieNode->next->m = classic;
									prevMovieNode->next->maxStock = stockAmount;
									prevMovieNode->next->stock = stockAmount;
									prevMovieNode->next->next = NULL;
									break;
								}
							}
							else if (classic->getActor()[0] < c->getActor()[0])
							{
								prevMovieNode->next = new movieNode;
								prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = currMovieNode;
								break;
							}
							else if (classic->getActor()[0] > c->getActor()[0])
							{
								prevMovieNode = currMovieNode;
								prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
							}
						}
						else if (classic->getDay() > c->getDay())
						{
							prevMovieNode = currMovieNode;
							prevC = dynamic_cast<Classic*>(currMovieNode->m);
							currMovieNode = currMovieNode->next;
							if (currMovieNode == NULL)
							{
								prevMovieNode->next = new movieNode;
								prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = NULL;
								break;
							}
						}
						else if (classic->getDay() < c->getDay())
						{
							prevMovieNode->next = new movieNode;
							prevMovieNode->next->m = classic;
							prevMovieNode->next->maxStock = stockAmount;
							prevMovieNode->next->stock = stockAmount;
							prevMovieNode->next->next = currMovieNode;
							break;
						}
					}
				}
			}*/
		}
		else if (Comedy *comedy = dynamic_cast<Comedy*>(newMovie))
		{

		}

		curr = curr->nextGenre;

	}

}