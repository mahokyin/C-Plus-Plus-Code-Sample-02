#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include "customer.h"
#include "movie.h"
#include "classic.h"
#include <time.h>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////Start with moive part//////////////////////////////////////////////////////////////

struct movieNode { //struct to store the information about the movies
	Movie *m;
	int stock;
	int maxStock;
	movieNode *next = NULL;
	movieNode *prev = NULL;
};
struct movieHead {  // struct to store the information about the different genres, and
					//holds the head of the movieNode of that genre.
	string genre;
	movieHead *nextGenre = NULL; //down pointer
	movieNode *first = NULL;	  //right pointer
};

movieHead *head = NULL; // holds all the information about the movies in the store. can be viewed as
						// linked list of linked lists.
////////////////////////////////////////////////////////////////////////////


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
	else if (Classic *obj = dynamic_cast<Classic*>(movie))
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
			if (newClassic->getActor()[0] == static_cast<Classic*>(currPtr->movie)->getActor()[0]) {
				insertMovieNode(newClassic, stockAmount, currPtr);
				return true;
			} else if (newClassic->getActor()[0] < static_cast<Classic*>(currPtr->movie)->getActor()[0]) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newClassic, stockAmount, 0, currPtr);
				else
					// normal case
					insertMovieNode(newClassic, stockAmount, currPtr->prev);
				return true;
			}
			else currPtr = currPtr->next;
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

bool addMovie2(Movie *newMovie, int stockAmount) {
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
			return addClassic(static_cast<Classic*>(newMovie), stockAmount);
		else
			return addClassic(static_cast<Classic*>(newMovie), stockAmount);
	}
}

void addMovie(Movie *newMovie, int stockAmount) {
	movieHead *curr = head;
	while (curr->nextGenre != NULL)
	{
		if (Classic *classic = dynamic_cast<Classic*>(newMovie))
		{
			if (curr->genre == "classic")
			{

				if (curr->first == NULL)
				{
					curr->first = new movieNode;
					curr->first->maxStock = stockAmount;
					curr->first->stock = stockAmount;
					curr->first->next = NULL;
					curr->first->prev = NULL;
					curr->first->m = classic;
				}
				else
				{

					movieNode *currMovieNode = curr->first;
					Classic *currClassic = dynamic_cast<Classic*>(currMovieNode->m);	

					while (currMovieNode != NULL)
					{

						if (currClassic->getDay() == classic->getDay())
						{
							if (classic->getActor()[0] == currClassic->getActor()[0])
							{
								//prevMovieNode = currMovieNode;
								//prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
								if (currMovieNode == NULL)
								{
									/*prevMovieNode->next = new movieNode;
									prevMovieNode->next->m = classic;
									prevMovieNode->next->maxStock = stockAmount;
									prevMovieNode->next->stock = stockAmount;
									prevMovieNode->next->next = NULL;
									break;*/
								}
							}
							else if (classic->getActor()[0] < currClassic->getActor()[0])
							{
								//prevMovieNode->next = new movieNode;
								/*prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = currMovieNode;
								break;*/
							}
							else if (classic->getActor()[0] > currClassic->getActor()[0])
							{
								//prevMovieNode = currMovieNode;
								//prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
							}
						}
						else if (classic->getDay() > currClassic->getDay())
						{
							movieNode *prevPtr = currMovieNode;
							currMovieNode = currMovieNode->next;
							if (currMovieNode != NULL)
								currClassic = dynamic_cast<Classic*>(currMovieNode->m);
							if (currMovieNode == NULL)
							{
								prevPtr->next = new movieNode;
								prevPtr->next->m = classic;
								prevPtr->next->maxStock = stockAmount;
								prevPtr->next->stock = stockAmount;
								prevPtr->next->next = NULL;
								prevPtr->next->prev = prevPtr;
								break;
							}
						}
						else if (classic->getDay() < currClassic->getDay())
						{
							movieNode *newNode = new movieNode;
							newNode->m = classic;
							newNode->maxStock = newNode->stock = stockAmount;
							
							// curr = head
							if (currMovieNode->prev == NULL) {
								newNode->prev = NULL;
								newNode->next = currMovieNode;
								currMovieNode->prev = newNode;
								curr->first = newNode;
							}
							else { // normal case
								movieNode *prevPtr = currMovieNode->prev;
								prevPtr->next = newNode;
								newNode->prev = prevPtr;
								newNode->next = currMovieNode;
								currMovieNode->prev = newNode;
							}
							break;
						}
					}
				}
			}
		}
		
		curr = curr->nextGenre;
	}
}

void constructor() {
	// Testing of the MovieStore Constructor
	head = new movieHead;
	head->nextGenre = new movieHead;
	head->nextGenre->genre = "classic";
	head->nextGenre->nextGenre = new movieHead;
	head->nextGenre->nextGenre->genre = "comedy";
	head->nextGenre->nextGenre->nextGenre = new movieHead;
	head->nextGenre->nextGenre->nextGenre->genre = "drama";
	head->nextGenre->nextGenre->nextGenre->nextGenre = NULL;
	//
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
		if (addMovie2(movie, 20)) cout << "T ";
		else cout << "F ";
		movie = new Classic("Joe", "Lenovo", 1000, "classic", "K", 1000);
		addMovie2(movie, 20);
		//cout << addMovie2(movie, 20);
	}
	cout << endl;

	Movie *movie = new Classic("Joe", "Lenovo", 1000, "classic", "Z", 1000);
	addMovie2(movie, 20);
	movie = new Classic("Joe", "Lenovo", 1000, "classic", "Z", 1000);
	addMovie2(movie, 20);
	movie = new Classic("Joe", "Lenovo", 1000, "classic", "K", 1000);
	addMovie2(movie, 20);
	movie = new Classic("Joe", "Lenovo", 1000, "classic", "F", 1000);
	addMovie2(movie, 20);
	movie = new Classic("Joe", "Lenovo", 1000, "classic", "R", 1000);
	addMovie2(movie, 20);
	movie = new Classic("Joe", "Lenovo", 1000, "classic", "E", 1000);
	addMovie2(movie, 20);
	cout << endl;

	for (MovieHashNode *ptr = movieHashtable[0]; ptr != NULL; ptr = ptr->next) {
		cout << static_cast<Classic*>(ptr->movie)->getYear() <<
			"  " << static_cast<Classic*>(ptr->movie)->getActor() << " " << endl;
	}
	
	
	system("pause");
	return 0;
}

