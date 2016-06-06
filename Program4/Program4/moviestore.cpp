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
	if(readCustomerData(inputCustomer)) cout << "Succesful read customer data !" << endl;
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
}

void MovieStore::displayAllCustomer() {
	cout << "ID" << setw(23) << "Frist name" << setw(23) << "Last name \n";
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