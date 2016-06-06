#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include "transaction.h"
#include "moviestore.h"
#include "borrow.h"

using namespace std;

int main()
{
	//string genre; //genre
	//int stock = 0; //stock
	//string movieName;
	//string director;
	//int movieYear;
	//int movieDay;
	//string firstName;
	//string lastName;


	//ifstream movieTextFile("data4movies.txt");
	//if (!movieTextFile) cout << "movie error" << endl;

	//while (!movieTextFile.eof())
	//{
	//	movieTextFile >> genre;
	//	genre = genre[0];

	//	if (genre == "F" || genre == "D")
	//	{
	//		movieTextFile.get();
	//		movieTextFile >> stock;

	//		movieTextFile.get();
	//		getline(movieTextFile, director, ',');

	//		movieTextFile.get();
	//		getline(movieTextFile, movieName, ',');

	//		movieTextFile.get();
	//		movieTextFile >> movieYear;

	//		cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |Year|: " << movieYear << endl;
	//	}
	//	else if (genre == "C" || genre == "Z")
	//	{
	//		movieTextFile.get();
	//		movieTextFile >> stock;

	//		movieTextFile.get();
	//		getline(movieTextFile, director, ',');

	//		movieTextFile.get();
	//		getline(movieTextFile, movieName, ',');

	//		movieTextFile.get();
	//		movieTextFile >> firstName;

	//		movieTextFile.get();
	//		movieTextFile >> lastName;

	//		movieTextFile.get();
	//		movieTextFile >> movieDay;

	//		movieTextFile.get();
	//		movieTextFile >> movieYear;

	//		cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |First|: " << firstName << " |Second|: " << lastName << " |Day|: " << movieDay << " |Year|: " << movieYear << endl;
	//	}
	//}



	string singleLine;
	Transaction *T;
	MovieStore M;
	vector <Transaction*> typeHolder;

	ifstream movieTextFile("data4commands.txt");
	if (!movieTextFile) cout << "movie error" << endl;

	while (!movieTextFile.eof())
	{
		//Gets a line from the data file and saves it into variable "singleLine"
		getline(movieTextFile, singleLine);	
		//Calls function genTrans which will return an instance of one of the child classes of transaction
		//depending on the first character in the file. With that instance, execute is called, which is an
		//overloaded function and takes a type MovieClass, and the singleLine.

		if (singleLine[0] == 'I' || singleLine[0] == 'H' || singleLine[0] == 'B' || singleLine[0] == 'R')
		{
			(T->genTrans(singleLine))->execute(M, singleLine);
		}
		else
		{
			cout << "invalid character input" << endl;
		}

		/*
		if (singleLine[0] == 'B')
		{
			//(T->genTrans(singleLine))->execute(M, singleLine);
			Borrow B;
			B.execute(M, singleLine);
		}
		else
		{
			cout << "invalid character input" << endl;
		}*/
		

		//typeHolder.push_back(T->genTrans(singleLine));
	}

	//for (int i = 0; i < typeHolder.size(); i++)
	//{
		//if (typeHolder[i] != Borrow )
	//}










	return 0;
}