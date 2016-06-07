//#include "transaction.h"
#include "inventory.h"
#include<iomanip>
using namespace std;

Inventory::Inventory()
{
	for (int i = 0; i < 3; i++)
		movieHashtable[i] = NULL;
	cout << "Initilize the movie hashtable successfully" << endl;
}

int Inventory::hashMovieByObj(Movie *movie) {
	// index 0---> Classic
	if (Classic *obj = dynamic_cast<Classic*>(movie))
		return 0;
		// index 1---> Comedy
	else if (Comedy *obj = dynamic_cast<Comedy*>(movie))
		return 1;
		// index 2----> Dramma
	else return 2;
}

void Inventory::displayInventory() {
	cout << internal << endl;
	cout << "Comedy" << endl;
	cout << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(26) << "Year \n";
	MovieHashNode *nodePtr = movieHashtable[1];
	while (nodePtr != NULL) {
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
		<< setw(25) << nodePtr->movie->getTitle() << setw(20) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;

	cout << "Dramma" << endl;
	cout << internal << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(26) << "Year \n";
	nodePtr = movieHashtable[2];
	while (nodePtr != NULL) {
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
		<< setw(25) << nodePtr->movie->getTitle() << setw(20) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;

	cout << "Classic" << endl;
	cout << internal << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(20) << "Actor" << setw(22) << "Month" << setw(18) << "Year" << endl;
	nodePtr = movieHashtable[0];
	while (nodePtr != NULL) {
		Classic *classObj = static_cast<Classic*>(nodePtr->movie);
		cout << left << setw(10) << nodePtr->stock << setw(20) << classObj->getDirector()
		<< setw(20) << classObj->getTitle() << setw(18) << classObj->getActor() << setw(22) << 
			classObj->getMonth() << setw(18) << classObj->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;
}

bool Inventory::addMovie(Movie *newMovie, int stockAmount) {
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

bool Inventory::addComedy(Comedy *newComedy, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[1];
	while (currPtr != NULL)
	{
		if (*newComedy == *static_cast<Comedy*>(currPtr->movie))
		{
			// Then compare the year
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

bool Inventory::addDrama(Drama *newDrama, int stockAmount) {
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

bool Inventory::addClassic(Classic *newClassic, int stockAmount) {
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


void Inventory::insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev) {
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

void Inventory::addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead) {
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->maxStock = stockAmount;
	newNode->stock = stockAmount;
	newNode->prev = NULL;
	newNode->next = oldHead;
	oldHead->prev = newNode;
	movieHashtable[index] = newNode;
}
