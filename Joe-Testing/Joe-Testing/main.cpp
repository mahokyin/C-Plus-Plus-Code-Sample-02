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
CustomerHashNode *customerHashTable[10];
////////////////////////////////////////////////////////////

int hashCustomerID(int id) {
	string strID = to_string(id);
	return strID[0] - 48;
}

void addCustomer(Customer &customer) {
	int index = hashCustomerID(customer.customerID);
	if (customerHashTable[index] == NULL) {
		// if no collision
		CustomerHashNode *head = new CustomerHashNode;
		head->customer = customer;
		head->next = NULL;
		customerHashTable[index] = head;
	} else {
		// Solution of collision
		CustomerHashNode *newHead = new CustomerHashNode;
		newHead->customer = customer;
		newHead->next = customerHashTable[index];
		customerHashTable[index] = newHead;
	}
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
		CustomerHashNode *currentNode = customerHashTable[i];
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
	delete[] customerHashTable;
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
					Classic *c = dynamic_cast<Classic*>(currMovieNode->m);	

					while (currMovieNode != NULL)
					{

						if (c->getDay() == classic->getDay())
						{
							if (classic->getActor()[0] == c->getActor()[0])
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
							else if (classic->getActor()[0] < c->getActor()[0])
							{
								//prevMovieNode->next = new movieNode;
								/*prevMovieNode->next->m = classic;
								prevMovieNode->next->maxStock = stockAmount;
								prevMovieNode->next->stock = stockAmount;
								prevMovieNode->next->next = currMovieNode;
								break;*/
							}
							else if (classic->getActor()[0] > c->getActor()[0])
							{
								//prevMovieNode = currMovieNode;
								//prevC = dynamic_cast<Classic*>(currMovieNode->m);
								currMovieNode = currMovieNode->next;
							}
						}
						else if (classic->getDay() > c->getDay())
						{
							movieNode *prevPtr = currMovieNode;
							currMovieNode = currMovieNode->next;
							if (currMovieNode != NULL)
								c = dynamic_cast<Classic*>(currMovieNode->m);
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
						else if (classic->getDay() < c->getDay())
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
	
	system("pause");
	return 0;
}

