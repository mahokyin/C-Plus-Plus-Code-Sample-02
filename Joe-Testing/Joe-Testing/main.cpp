#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include "customer.h"
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
using namespace std;


////////////////////////////////////////////////////////////
// Structure of hashtable and hashNode for Customer object
struct CustomerHashNode {
	Customer customer;
	CustomerHashNode *next;
};
CustomerHashNode *customerHashtable[10];
////////////////////////////////////////////////////////////

int hashCustomerID(int id) {
	string strID = to_string(id);
	return strID[0] - 48;
}

bool addCustomer(Customer &customer) {
	int index = hashCustomerID(customer.customerID);
	if (customerHashtable[index] == NULL) {
		// if no collision
		CustomerHashNode *head = new CustomerHashNode;
		head->customer = customer;
		head->next = NULL;
		customerHashtable[index] = head;
		return true;
	} else {
		// Solution of collision
		CustomerHashNode *newHead = new CustomerHashNode;
		newHead->customer = customer;
		newHead->next = customerHashtable[index];
		customerHashtable[index] = newHead;
		return true;
	}
	return false;
}

bool readCustomerData(ifstream &input) {
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

// Not sure yet.
void clearCustomer() {
	for (int i = 0; i < 10; i++) {
		CustomerHashNode *currentNode = customerHashtable[i];
		while (currentNode != NULL) {
			CustomerHashNode *oldPtr = currentNode;
			currentNode = currentNode->next;
			delete oldPtr; oldPtr = NULL;
		}
	}
}

// Not sure yet;
void clearCustomerTable() {
	clearCustomer();
	delete[] customerHashtable;
}


// Structure of hashtable and hashNode for Movie object
struct MovieHashNode {
	Movie *movie = NULL;
	int stock;
	int maxStock;
	MovieHashNode *next = NULL;
	MovieHashNode *prev = NULL;
};
MovieHashNode *movieHashtable[3];

int hashMovieByObj(Movie *movie) {
	// index 0---> Classic
	if (Classic *obj = dynamic_cast<Classic*>(movie))
		return 0;
	// index 1---> Comedy
	else if (Comedy *obj = dynamic_cast<Comedy*>(movie))
		return 1;
	// index 2----> Dramma
	else return 2;
}
////////////////////////////////////////////////////////////

void insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev) {
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
	}
}

void addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead) {
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->maxStock = stockAmount;
	newNode->stock = stockAmount;
	newNode->prev = NULL;
	newNode->next = oldHead;
	oldHead->prev = newNode;
	movieHashtable[index] = newNode;
}

bool addClassic(Classic *newClassic, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[0];
	while (currPtr != NULL) 
	{
		if (*newClassic == *static_cast<Classic*>(currPtr->movie)) 
		{
			// With same char 
			if (toupper(newClassic->getActor()[0]) == toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
				insertMovieNode(newClassic, stockAmount, currPtr);
				return true;
			} else if (toupper(newClassic->getActor()[0]) < toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
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

bool addComedy(Comedy *newComedy, int stockAmount) {
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

bool addDrama(Drama *newDrama, int stockAmount) {
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

bool addMovie(Movie *newMovie, int stockAmount) {
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

int main() {
	srand(time(NULL));
	/*
	ifstream idTextFile("data4customers.txt");
	readCustomerData(idTextFile);

	CustomerHashNode *nodePtr;
	for (int i = 0; i < 10; i++) {
		nodePtr = customerHashTable[i];
		while (nodePtr != NULL) {
			cout << nodePtr->customer.customerID << " ";
			nodePtr = nodePtr->next;
		}
		cout << endl;
	}
	clearCustomerTable();
	*/

	/*
	constructor();

	movieHead *currHead = head;
	while (currHead != NULL) {
		cout << currHead->genre << endl;
		currHead = currHead->nextGenre;
	}
	// Done with constructor

	for (int i = 0; i < 10; i++) {
		int randNum = rand() % 9000 + 1000;
		Movie *movie = new Classic("Joe", "Lenovo", randNum, "classic", "Andrey", randNum);
		cout << randNum << " ";
		addMovie(movie, 20);
	}
	cout << endl;

	currHead = head;
	while (currHead->nextGenre != NULL) {
		for (movieNode *node = currHead->first; node != NULL; node = node->next) {
			Classic *cMovie = dynamic_cast<Classic*>(node->m);
			cout << cMovie->getDay() << " ";
		}
		currHead = currHead->nextGenre;
		cout << endl;
	}
	*/

	/*
	for (int i = 0; i < 10; i++) {
		int randNum = rand() % 9000 + 1000;
		Movie *movie = new Classic("Joe", "Lenovo", randNum, "classic", "Andrey", randNum);
		cout << randNum << " ";
		if (addMovie2(movie, 20)) cout << "T ";
		else cout << "F ";
		//cout << addMovie2(movie, 20);
	}
	cout << endl;
	
	for (MovieHashNode *ptr = movieHashtable[0]; ptr != NULL; ptr = ptr->next) {
		cout << static_cast<Classic*>(ptr->movie)->getDay() << " ";
	}

	cout << endl;
	*/

	for (int i = 0; i < 10; i++) {
		int randNum = rand() % 9000 + 1000;
		Movie *movie = new Classic("Joe", "Lenovo", randNum, "classic", "Andrey", randNum);
		cout << randNum << " ";
		if (addMovie(movie, 20)) cout << "T ";
		else cout << "F ";
		movie = new Classic("Joe", "Lenovo", 1000, "classic", "K", 1000);
		addMovie(movie, 20);
		//cout << addMovie2(movie, 20);
	}
	cout << endl;

	/*Movie *movie = new Comedy("Joe", "a", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "REWT", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "GDHd", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "WTRWEt", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "SFGs", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "SFGS", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "WTRWEt", 2000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "WTRWEt", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "WTRWEt", 4000, "t");
	cout << addMovie(movie, 20);
	movie = new Comedy("Joe", "WTRWEt", 3000, "t");
	cout << addMovie(movie, 20);
	cout << endl;*/

	Movie *movie = new Drama("Joe", "a", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("GF", "REWT", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("VD", "GDHd", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("SGF", "WTRWEt", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("AW", "SFGs", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("HL", "SFGS", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("OO", "GH", 2000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("OO", "AB", 2000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("OO", "PO", 2000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("OO", "ZC", 2000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("FG", "WTRWEt", 1000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("Q", "WTRWEt", 4000, "t");
	cout << addMovie(movie, 20);
	movie = new Drama("J", "WTRWEt", 3000, "t");
	cout << addMovie(movie, 20);
	cout << endl;

	for (MovieHashNode *ptr = movieHashtable[2]; ptr != NULL; ptr = ptr->next) {
		cout << static_cast<Drama*>(ptr->movie)->getDirector() <<
			"  " << static_cast<Drama*>(ptr->movie)->getTitle() << " " << endl;
	}
	
	
	system("pause");
	return 0;
}

