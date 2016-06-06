#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "moviestore.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"
#include "customer.h"
//#include "transaction.h"
//#include "borrow.h"
//#include "inventory.h"
//#include "return.h"
//#include "history.h"

//#include "customer.h"

using namespace std;



#include "moviestore.h"
#include<iomanip>
using namespace std;

MovieStore::MovieStore() {

}

MovieStore::MovieStore(ifstream &inputCustomer, ifstream &inputMovie) {
	for (int i = 0; i < 10; i++)
		customerHashtable[i] = NULL;
	for (int i = 0; i < 3; i++)
		movieHashtable[i] = NULL;
	if (readCustomerData(inputCustomer)) cout << "Succesful read customer data !" << endl;
	else cout << "Failure to read data !" << endl;
	if (readMovieData(inputMovie)) cout << "Succesful read movie data !" << endl;
	else cout << "Failure to read data !" << endl;
}

int MovieStore::hashCustomerID(int id) {
	string strID = to_string(id);
	return strID[0] - 48;
}

int MovieStore::hashMovieByObj(Movie *movie) {
	// index 0---> Classic
	if (Classic *obj = dynamic_cast<Classic*>(movie))
		return 0;
	// index 1---> Comedy
	else if (Comedy *obj = dynamic_cast<Comedy*>(movie))
		return 1;
	// index 2----> Dramma
	else return 2;
}

bool MovieStore::addCustomer(Customer &customer) {
	int index = hashCustomerID(customer.customerID);
	if (customerHashtable[index] == NULL) {
		// if no collision
		CustomerHashNode *head = new CustomerHashNode;
		head->customer = customer;
		head->next = NULL;
		customerHashtable[index] = head;
		return true;
	}
	else {
		// Solution of collision
		CustomerHashNode *newHead = new CustomerHashNode;
		newHead->customer = customer;
		newHead->next = customerHashtable[index];
		customerHashtable[index] = newHead;
		return true;
	}
	return false;
}

bool MovieStore::addMovie(Movie *newMovie, int stockAmount) {
	int index = hashMovieByObj(newMovie);
	if (movieHashtable[index] == NULL) {
		MovieHashNode *head = new MovieHashNode;
		head->movie = newMovie;
		head->stock = head->maxStock = stockAmount;
		head->prev = NULL; head->next = NULL;
		movieHashtable[index] = head;
		return true;
	}
	else {
		if (index == 0)
			return addClassic(static_cast<Classic*>(newMovie), stockAmount);
		else if (index == 1)
			return addComedy(static_cast<Comedy*>(newMovie), stockAmount);
		else
			return addDrama(static_cast<Drama*>(newMovie), stockAmount);
	}
}

bool MovieStore::addClassic(Classic *newClassic, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[0];
	while (currPtr != NULL)
	{
		if (*newClassic == *static_cast<Classic*>(currPtr->movie))
		{
			// With same char 
			if (toupper(newClassic->getActor()[0]) == toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
				insertMovieNode(newClassic, stockAmount, currPtr);
				return true;
			}
			else if (toupper(newClassic->getActor()[0]) < toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newClassic, stockAmount, 0, currPtr);
				else
					// normal case
					insertMovieNode(newClassic, stockAmount, currPtr->prev);
				return true;
			}
			else {
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next;
				if (currPtr == NULL) {
					insertMovieNode(newClassic, stockAmount, prevPtr);
					return true;
				}
			}
		}
		else if (*newClassic > *static_cast<Classic*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newClassic, stockAmount, prevPtr);
				return true;
			}
		}
		else if (*newClassic < *static_cast<Classic*>(currPtr->movie))
		{
			// curr = head
			if (currPtr->prev == NULL)
				addFirstMovieNode(newClassic, stockAmount, 0, currPtr);
			else
				// normal case
				insertMovieNode(newClassic, stockAmount, currPtr->prev);
			return true;
		}
	}
	return false;
}

bool MovieStore::addComedy(Comedy *newComedy, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[1];
	while (currPtr != NULL)
	{
		if (*newComedy == *static_cast<Comedy*>(currPtr->movie))
		{
			// With same char 
			if (newComedy->getYear() == static_cast<Comedy*>(currPtr->movie)->getYear()) {
				insertMovieNode(newComedy, stockAmount, currPtr);
				return true;
			}
			else if (newComedy->getYear() < static_cast<Comedy*>(currPtr->movie)->getYear()) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newComedy, stockAmount, 1, currPtr);
				else
					// normal case
					insertMovieNode(newComedy, stockAmount, currPtr->prev);
				return true;
			}
			else
			{
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next;
				if (currPtr == NULL) {
					insertMovieNode(newComedy, stockAmount, prevPtr);
					return true;
				}
			}
		}
		else if (*newComedy > *static_cast<Comedy*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newComedy, stockAmount, prevPtr);
				return true;
			}
		}
		else if (*newComedy < *static_cast<Comedy*>(currPtr->movie))
		{
			// curr = head
			if (currPtr->prev == NULL)
				addFirstMovieNode(newComedy, stockAmount, 1, currPtr);
			else
				// normal case
				insertMovieNode(newComedy, stockAmount, currPtr->prev);
			return true;
		}
	}
	return false;
}

bool MovieStore::addDrama(Drama *newDrama, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[2];
	while (currPtr != NULL)
	{
		if (*newDrama == *static_cast<Drama*>(currPtr->movie))
		{
			// With same char 
			if (newDrama->getTitle() == static_cast<Drama*>(currPtr->movie)->getTitle()) {
				insertMovieNode(newDrama, stockAmount, currPtr);
				return true;
			}
			else if (newDrama->getTitle() < static_cast<Drama*>(currPtr->movie)->getTitle()) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newDrama, stockAmount, 2, currPtr);
				else
					// normal case
					insertMovieNode(newDrama, stockAmount, currPtr->prev);
				return true;
			}
			else
			{
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next;
				if (currPtr == NULL) {
					insertMovieNode(newDrama, stockAmount, prevPtr);
					return true;
				}
			}
		}
		else if (*newDrama > *static_cast<Drama*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newDrama, stockAmount, prevPtr);
				return true;
			}
		}
		else if (*newDrama < *static_cast<Drama*>(currPtr->movie))
		{
			// curr = head
			if (currPtr->prev == NULL)
				addFirstMovieNode(newDrama, stockAmount, 2, currPtr);
			else
				// normal case
				insertMovieNode(newDrama, stockAmount, currPtr->prev);
			return true;
		}
	}
	return false;
}

void MovieStore::insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev) {
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->maxStock = stockAmount;
	newNode->stock = stockAmount;
	if (prev->next != NULL) {
		MovieHashNode *next = prev->next;
		newNode->prev = prev;
		newNode->next = next;
		prev->next = newNode;
		next->prev = newNode;
	}
	else {
		prev->next = newNode;
		newNode->prev = prev;
		newNode->next = NULL;
	}
}

void MovieStore::addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead) {
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->maxStock = stockAmount;
	newNode->stock = stockAmount;
	newNode->prev = NULL;
	newNode->next = oldHead;
	oldHead->prev = newNode;
	movieHashtable[index] = newNode;
}
/*
bool MovieStore::readCustomerData(ifstream &input) {
	string str;
	if (!input) return false;
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str)) {
		string id; string lastname; string firstname;
		istringstream(str) >> id >> lastname >> firstname;
		Customer customer(stoi(str), firstname, lastname);
		addCustomer(customer);
	}
	return true;
}


bool MovieStore::readMovieData(ifstream &input) {
	string str;
	if (!input) return false;
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str, ',')) {
		string type;
		istringstream(str) >> type;
		if (type == "F" || type == "D") {
			string stock, director, title, year;
			getline(input, stock, ',');
			getline(input, director, ',');
			getline(input, title, ',');
			getline(input, year, '\n');
			if (type == "F") cout << addMovie(new Comedy(director, title, stoi(year), "F"), stoi(stock));
			else cout << addMovie(new Drama(director, title, stoi(year), "D"), stoi(stock));
		}
		else if (type == "C") {
			string stock, director, title, year, actorFirstname, actorLastname, day;
			getline(input, stock, ',');
			getline(input, director, ',');
			getline(input, title, ',');
			getline(input, str);
			istringstream(str) >> actorFirstname >> actorLastname >> day >> year;
			cout << addMovie(new Classic(director, title, stoi(year), "F", actorFirstname + " " + actorLastname, stoi(day)), stoi(stock));
		}
		else getline(input, str, '\n');
	}
	return true;
}*/

void MovieStore::displayAllCustomer() {
	cout << "ID" << setw(23) << "First name" << setw(23) << "Last name \n";
	CustomerHashNode *nodePtr;
	for (int i = 0; i < 10; i++) {
		nodePtr = customerHashtable[i];
		while (nodePtr != NULL) {
			cout << nodePtr->customer.customerID << setw(20) << nodePtr->customer.firstName << setw(20) << nodePtr->customer.lastName << endl;
			nodePtr = nodePtr->next;
		}
	}
	cout << endl;
}

void MovieStore::displayAllMovie() {
	cout << "Stock" << setw(23) << "Director" << setw(23) << "Title" << setw(23) << "Year \n";
	MovieHashNode *nodePtr;
	for (int i = 0; i < 3; i++) {
		nodePtr = movieHashtable[i];
		while (nodePtr != NULL) {
			cout << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
				<< setw(20) << nodePtr->movie->getTitle() << setw(20) << nodePtr->movie->getYear() << endl;
			nodePtr = nodePtr->next;
		}
	}
	cout << endl;
}

void MovieStore::displayCustomerHistory(int customerID)
{
	cout << "Customer ID: " << customerID << " ";

	//Convert Id to hash id
	customerID = hashCustomerID(customerID);

	cout << customerHashtable[customerID]->customer.firstName << " " << customerHashtable[customerID]->customer.lastName << endl;

	//Display the customers history, implimented in customer classF
	customerHashtable[customerID]->customer.displayHistory();
}

bool MovieStore::borrowMovie(string line)
{
	int	customerID;
	char mediaType;
	string movieType;
	string movieName;
	string directorName;
	int movieYear;
	int movieMonth;
	int counter = 11;
	int movieNameCounter = 0;
	string action = "b"; //For borrow, will be 'r' for return, used for helper function canBorrow

	//Get the customer id
	customerID = (line[2] - '0') * 1000;
	customerID += (line[3] - '0') * 100;
	customerID += (line[4] - '0') * 10;
	customerID += line[5] - '0';

	//Convert to hash id
	customerID = hashCustomerID(customerID);

	mediaType = line[7];
	movieType[0] = line[9];
	
	//Check the movie genre type
	if (movieType == "F")/////////////////////Comedy
	{
		//Get the name of the movie
		while (line[counter] != ',')
		{
			movieName[movieNameCounter] = line[counter];
			counter++;
		}

		//Get the year of the movie
		movieYear = (line[counter + 2] - '0') * 1000;
		movieYear += (line[counter + 3] - '0') * 100;
		movieYear += (line[counter + 4] - '0') * 10;
		movieYear += line[counter + 5] - '0';

		//Loop until you have reahed the end of the movie linked list or found the movie you looking for
		while (movieHashtable[1]->next != NULL)
		{
			//Check if title and year match up
			if (movieHashtable[1]->movie->getTitle() == movieName && movieHashtable[1]->movie->getYear() == movieYear)
			{
				//Check if there is still stock
				if (movieHashtable[1]->stock > 0)
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canBorrow(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[1]->stock -= 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear); /////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You are currently borrowing this movie" << endl;
						return false;
					}
				}
				else
				{
					cout << "Movie is out of stock" << endl;
					return false;
				}

				//If that wasnt the correct movie move on to the next one
				movieHashtable[1]->next = movieHashtable[1]->next->next;
			}
		}	
	}
	else if (movieType == "D") /////////////////////////Drama
	{
		//Get the name of the director
		while (line[counter] != ',')
		{
			directorName[movieNameCounter] = line[counter];
			counter++;
		}

		//Get the name of the movie
		movieNameCounter = 0; 
		counter += 2;
		while (line[counter] != ',')
		{
			movieName[movieNameCounter] = line[counter];
			counter++;
		}

		//Loop until you have reahed the end of the movie linked list or found the movie you looking for
		while (movieHashtable[2]->next != NULL)
		{
			//Check if title and year match up
			if (movieHashtable[2]->movie->getTitle() == movieName && movieHashtable[2]->movie->getYear() == movieYear)
			{
				//Check if there is still stock
				if (movieHashtable[2]->stock > 0)
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canBorrow(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[2]->stock -= 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear);/////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You are currently borrowing this movie" << endl;
						return false;
					}
				}
				else
				{
					cout << "Movie is out of stock" << endl;
					return false;
				}

				//If that wasnt the correct movie move on to the next one
				movieHashtable[2]->next = movieHashtable[2]->next->next;
			}
		}
	}
	else if (movieType == "C") //////////////////////////////////////Classic
	{
		//Get the month of the movie
		movieMonth = line[11];

		//Get the year of the movie
		movieYear = (line[13] - '0') * 1000;
		movieYear += (line[14] - '0') * 100;
		movieYear += (line[15] - '0') * 10;
		movieYear += line[16] - '0';

		counter = 18;
		movieNameCounter = 0;
		//Get the name of the director
		while (line[counter] != ',')
		{
			directorName[movieNameCounter] = line[counter];
			counter++;
		}

		//Loop until you have reahed the end of the movie linked list or found the movie you looking for
		while (movieHashtable[0]->next != NULL)
		{
			//Check if title and year match up
			if (movieHashtable[0]->movie->getTitle() == movieName && movieHashtable[0]->movie->getYear() == movieYear)
			{
				//Check if there is still stock
				if (movieHashtable[0]->stock > 0)
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canBorrow(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[0]->stock -= 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear);/////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You are currently borrowing this movie" << endl;
						return false;
					}
				}
				else
				{
					cout << "Movie is out of stock" << endl;
					return false;
				}

				//If that wasnt the correct movie move on to the next one
				movieHashtable[0]->next = movieHashtable[0]->next->next;
			}
		}
	}
	else
	{
		cout << "The movie type is invalid" << endl;
		return false;
	}
	

	cout << "Movie could not be found" << endl;
	return false;

	//cout << "customerID: " << customerID << " media type: " << mediaType << " movie type: " << movieType << " Movie name: " << movieName << " movie year: " << movieYear << endl;
}








/*
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
		{
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
			}
		}
		else if (Comedy *comedy = dynamic_cast<Comedy*>(newMovie))
		{

		}

		curr = curr->nextGenre;

	}

}*/