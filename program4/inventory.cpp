// ----------------------------------------------- inventory.cpp -------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - This header containes Inventory class that deals with adding, displaying, and searching the inventory of 
//			 the store. Also contains MovieHashNode, a struct that holders all the data nessesary for a movie node.
// ---------------------------------------------------------------------------------------------------------------------
#include "inventory.h"
#include <iomanip>

using namespace std;

// ---------------------------------------Constructor-------------------------------------
// Description: Initializes the movie hash table.
// ---------------------------------------------------------------------------------------
Inventory::Inventory()
{
	//Initialize the movie hashtable
	//3 indexes, one for each of the movie genres
	for (int i = 0; i < 3; i++)
		movieHashtable[i] = NULL;
}

// ---------------------------------------Destructor--------------------------------------
// Description: Deletes all the memory allocated in inventory.cpp.
// PostCondition: All memory will be released.
// ---------------------------------------------------------------------------------------
Inventory::~Inventory() {
	MovieHashNode *currPtr = NULL; //makes a temp pointer

	//Loop through the hash table deleting pointers
	for (int i = 0; i < 3; i++) {
		MovieHashNode *head = movieHashtable[i];
		while (head != NULL) { //Run through linked list of movies
			MovieHashNode *old = head;
			head = head->next;
			delete old; old = NULL;
		}
	}
}

// ------------------------------------hashMovieByObj-------------------------------------
// Description: Hashes the movies by the genre.
// PreCondition: Contructor must be implimented. Takes in the movie to check the type.
// PostCondition: Returns the index depending on the genre.
// ---------------------------------------------------------------------------------------
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

// ----------------------------------displayInventory-------------------------------------
// Description: Displays all the movies in the store, by running through the hash table.
// PreCondition: Contructor must be implimented.
// PostCondition: All movies will be displayed.
// ---------------------------------------------------------------------------------------
void Inventory::displayInventory() {
	cout << internal << endl << endl;
	cout << "|Comedy|" << endl;
	cout << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(36) << "Year \n";
	MovieHashNode *nodePtr = movieHashtable[1]; //Saves the index of the hash table to a pointer
	while (nodePtr != NULL) { //Loops through the linked list of movies
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
		<< setw(35) << nodePtr->movie->getTitle() << setw(34) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next; //Traverse the list
	}
	cout << endl;

	cout << "|Drama|" << endl;
	cout << internal << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(36) << "Year \n";
	nodePtr = movieHashtable[2]; //Saves the index of the hash table to a pointer
	while (nodePtr != NULL) { //Loops through the linked list of movies
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
		<< setw(35) << nodePtr->movie->getTitle() << setw(28) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next; //Traverse the list
	}
	cout << endl;

	cout << "|Classic|" << endl;
	cout << internal << "Stock" << setw(13) << "Director" << setw(17) << "Title" << setw(25) << "Actor" << setw(22) << "Month" << setw(14) << "Year" << endl;
	nodePtr = movieHashtable[0]; //Saves the index of the hash table to a pointer
	while (nodePtr != NULL) { //Loops through the linked list of movies
		Classic *classObj = static_cast<Classic*>(nodePtr->movie);
		cout << left << setw(10) << nodePtr->stock << setw(20) << classObj->getDirector()
		<< setw(25) << classObj->getTitle() << setw(23) << classObj->getActor() << setw(14) << 
			classObj->getMonth() << setw(15) << classObj->getYear() << endl;
		nodePtr = nodePtr->next; //Traverse the list
	}
	cout << endl;
}

// -------------------------------------addMovie-----------------------------------------
// Description: Creates a new movie Node, calls a helper function to insert the node into
//			    the correct location in the hashTables linked list.
// PreCondition: Hash table needs to be created. Takes in the movie and stock amount.
// PostCondition: Whichever genres the movie is, that ones helper function will be called.
// ---------------------------------------------------------------------------------------
bool Inventory::addMovie(Movie *newMovie, int stockAmount) {
	int index = hashMovieByObj(newMovie);

	//Creates the new movie node
	if (movieHashtable[index] == NULL) {
		MovieHashNode *head = new MovieHashNode;
		head->movie = newMovie;
		head->stock = stockAmount;
		head->prev = NULL; head->next = NULL;
		movieHashtable[index] = head;
		return true;
	}
	else {
		//Calls the helper function depending on the movie's genre
		if (index == 0)
			return addClassic(static_cast<Classic*>(newMovie), stockAmount);
		else if (index == 1)
			return addComedy(static_cast<Comedy*>(newMovie), stockAmount);
		else
			return addDrama(static_cast<Drama*>(newMovie), stockAmount);
	}
}

// -------------------------------------addComedy-----------------------------------------
// Description: Inserts the new comedy movie into the hash table and inserts it into the
//				correct location in the linked list.
// PreCondition: Hash table needs to be created. takes in the comedy and stock amount.
// PostCondition: Comedy movie is inserted into correct location of linked list.
// ---------------------------------------------------------------------------------------
bool Inventory::addComedy(Comedy *newComedy, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[1];
	while (currPtr != NULL) //Loop while not at the end of the list
	{
		if (*newComedy == *static_cast<Comedy*>(currPtr->movie))
		{
			// Then compare the year
			if (newComedy->getYear() == static_cast<Comedy*>(currPtr->movie)->getYear()) {
				insertMovieNode(newComedy, stockAmount, currPtr);
				return true;
			}
			//Years are not ==
			else if (newComedy->getYear() < static_cast<Comedy*>(currPtr->movie)->getYear()) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newComedy, stockAmount, 1, currPtr); //Call helper first node
				else
					// normal case
					insertMovieNode(newComedy, stockAmount, currPtr->prev); //Call helper all other cases
				return true;
			}
			else
			{
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next; //Traverse
				if (currPtr == NULL) {
					insertMovieNode(newComedy, stockAmount, prevPtr); //Call helper all other cases
					return true;
				}
			}
		}
		//The movie is greater(based off operator overloaded for comedy)
		else if (*newComedy > *static_cast<Comedy*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newComedy, stockAmount, prevPtr); //Call helper on normal case
				return true;
			}
		}
		//The movie is less(based off operator overloaded for comedy)
		else if (*newComedy < *static_cast<Comedy*>(currPtr->movie))
		{
			// curr = head
			if (currPtr->prev == NULL)
				addFirstMovieNode(newComedy, stockAmount, 1, currPtr); //First node case
			else
				// normal case
				insertMovieNode(newComedy, stockAmount, currPtr->prev); 
			return true;
		}
	}
	return false;
}

// -------------------------------------addDrama------------------------------------------
// Description: Inserts the new drama movie into the hash table and inserts it into the
//				correct location in the linked list.
// PreCondition: Hash table needs to be created. takes in the drama movie and stock amount.
// PostCondition: Drama movie is inserted into correct location of linked list.
// ---------------------------------------------------------------------------------------
bool Inventory::addDrama(Drama *newDrama, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[2];
	while (currPtr != NULL) //Loop till the end of the list
	{
		//Checks if the movies are equal depending on the operator overload for drama
		if (*newDrama == *static_cast<Drama*>(currPtr->movie))
		{
			// With same title
			if (newDrama->getTitle() == static_cast<Drama*>(currPtr->movie)->getTitle()) {
				insertMovieNode(newDrama, stockAmount, currPtr); //call helper for normal case
				return true;
			}
			else if (newDrama->getTitle() < static_cast<Drama*>(currPtr->movie)->getTitle()) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newDrama, stockAmount, 2, currPtr); //First node case
				else
					// normal case
					insertMovieNode(newDrama, stockAmount, currPtr->prev);
				return true;
			}
			else //Movie title is greater
			{
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next;
				if (currPtr == NULL) {
					insertMovieNode(newDrama, stockAmount, prevPtr); //call helper for normal case
					return true;
				}
			}
		} 
		else if (*newDrama > *static_cast<Drama*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newDrama, stockAmount, prevPtr); //call helper for normal case
				return true;
			}
		}
		else if (*newDrama < *static_cast<Drama*>(currPtr->movie))
		{
			// curr = head
			if (currPtr->prev == NULL)
				addFirstMovieNode(newDrama, stockAmount, 2, currPtr); //call helper for first node case
			else
				// normal case
				insertMovieNode(newDrama, stockAmount, currPtr->prev);
			return true;
		}
	}
	return false;
}

// -------------------------------------addClassic----------------------------------------
// Description: Inserts the new classic movie into the hash table and inserts it into the
//				correct location in the linked list.
// PreCondition: Hash table needs to be created. takes in the classic movie and stock amount.
// PostCondition: Classic movie is inserted into correct location of linked list.
// ---------------------------------------------------------------------------------------
bool Inventory::addClassic(Classic *newClassic, int stockAmount) {
	MovieHashNode *currPtr = movieHashtable[0];
	while (currPtr != NULL) //Loop till the end of the list
	{
		//Checks if the new movie is == to the current one
		if (*newClassic == *static_cast<Classic*>(currPtr->movie))
		{
			// With same char
			if (toupper(newClassic->getActor()[0]) == toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
				insertMovieNode(newClassic, stockAmount, currPtr); //Normal case insert
				return true;
			}
			else if (toupper(newClassic->getActor()[0]) < toupper(static_cast<Classic*>(currPtr->movie)->getActor()[0])) {
				// curr = head
				if (currPtr->prev == NULL)
					addFirstMovieNode(newClassic, stockAmount, 0, currPtr); //First node case
				else
					//Normal case insert
					insertMovieNode(newClassic, stockAmount, currPtr->prev);
				return true;
			}
			else { //The new movie's actor is greater than current movies
				MovieHashNode *prevPtr = currPtr;
				currPtr = currPtr->next;
				if (currPtr == NULL) {
					insertMovieNode(newClassic, stockAmount, prevPtr); //Normal insert case
					return true;
				}
			}
		}
		else if (*newClassic > *static_cast<Classic*>(currPtr->movie))
		{
			MovieHashNode *prevPtr = currPtr;
			currPtr = currPtr->next;
			if (currPtr == NULL) {
				insertMovieNode(newClassic, stockAmount, prevPtr); //Normal insert case
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

// --------------------------------insertMovieNode----------------------------------------
// Description: Inserts the new movie into the correct location in the linked list.
// PreCondition: Must recieve the correct movie, stock, and prev pointer.
// PostCondition: The movie will be inserted into the linked list.
// ---------------------------------------------------------------------------------------
void Inventory::insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev) {
	//makes a new node and adds info about it
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->stock = stockAmount;

	//Decides if at the end of the list or not
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

// ------------------------------addFirstMovieNode----------------------------------------
// Description: Inserts the new movie into the first location in the linked list.
// PreCondition: Must recieve the correct movie, stock, and prev pointer, head, and index.
// PostCondition: The movie will be inserted into the linked list.
// ---------------------------------------------------------------------------------------
void Inventory::addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead) {
	//Makes a new node and links it up to the front of the linekd list
	MovieHashNode *newNode = new MovieHashNode;
	newNode->movie = movie;
	newNode->stock = stockAmount;

	newNode->prev = NULL;
	newNode->next = oldHead;
	oldHead->prev = newNode;
	movieHashtable[index] = newNode;
}

// --------------------------------searchInventory----------------------------------------
// Description: Search through the inventory hash table for the movie provided.
// PreCondition: Must recieve the movie that is being searched for
// PostCondition: Returns a pointer to the node of the movie if found, else return null.
// ---------------------------------------------------------------------------------------
MovieHashNode *Inventory::searchInventory(Movie *movie) {
	MovieHashNode *currPtr = NULL;
	//Checks if movie is a classic
	if(Classic *obj = dynamic_cast<Classic*>(movie)) {
		currPtr = movieHashtable[0]; //Go to correct hash index
		while (currPtr != NULL) { //loop till end of the list
			Classic *stockObj = static_cast<Classic*>(currPtr->movie);
			//compare by day and actor
			if (*(stockObj) == *obj && stockObj->getActor() == obj->getActor()) {
				return currPtr;
			} else currPtr = currPtr->next;
		}
		//Checks if movie is a comedy
	} else if (Comedy *obj = dynamic_cast<Comedy*>(movie)) {
		currPtr = movieHashtable[1]; //Go to correct hash index
		while (currPtr != NULL) { //loop till end of the list
			Comedy *stockObj = static_cast<Comedy*>(currPtr->movie);
			//compare by year and title
			if (*stockObj == *obj && stockObj->getYear() == obj->getYear()) {
				return currPtr;
			} else currPtr = currPtr->next;
		}
		//Checks if movie is a drama
	} else if (Drama *obj = dynamic_cast<Drama*>(movie)) {
		currPtr = movieHashtable[2]; //Go to correct hash index
		while (currPtr != NULL) { //loop till end of the list
			Drama *stockObj = static_cast<Drama*>(currPtr->movie);
			//compare by director and title
			if (*stockObj == *obj && stockObj->getTitle() == obj->getTitle()) {
				return currPtr;
			} else currPtr = currPtr->next;
		}
	}
	return NULL;
}