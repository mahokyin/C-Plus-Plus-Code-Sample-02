#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	string genre; //genre
	int stock = 0; //stock
	string movieName;
	string director;
	int movieYear;
	int movieDay;
	string firstName;
	string lastName;


	ifstream movieTextFile("data4movies.txt");
	if (!movieTextFile) cout << "movie error" << endl;

	while (!movieTextFile.eof())
	{
		movieTextFile >> genre;
		genre = genre[0];

		if (genre == "F" || genre == "D")
		{
			movieTextFile.get();
			movieTextFile >> stock;

			movieTextFile.get();
			getline(movieTextFile, director, ',');

			movieTextFile.get();
			getline(movieTextFile, movieName, ',');

			movieTextFile.get();
			movieTextFile >> movieYear;

			cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |Year|: " << movieYear << endl;
		}
		else if (genre == "C" || genre == "Z")
		{
			movieTextFile.get();
			movieTextFile >> stock;

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

			cout << "|Genre|: " << genre << " |Stock|: " << stock << " |Director|: " << director << " |Movie Name|: " << movieName << " |First|: " << firstName << " |Second|: " << lastName << " |Day|: " << movieDay << " |Year|: " << movieYear << endl;
		}
	}

	return 0;
}