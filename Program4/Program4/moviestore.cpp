#include "moviestore.h"
#include "borrow.h"
#include "history.h"
#include "return.h"
#include "inventory.h"
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

void MovieStore::readCommandData(ifstream &input) {
	string str;
	if (!input) {
		cout << "File not found !" << endl;
	}
	// Need to add exception to handle the error if not found the file.

	string singleLine;

	while (!input.eof())
	{
		//Gets a line from the data file and saves it into variable "singleLine"
		getline(input, singleLine);
		//Calls function genTrans which will return an instance of one of the child classes of transaction
		//depending on the first character in the file. With that instance, execute is called, which is an
		//overloaded function and takes a type MovieClass, and the singleLine.

		if (singleLine[0] == 'I') {
			Inventory inventory;
			inventory.execute(*this, singleLine);
		} 
		else if (singleLine[0] == 'H')
		{
			History history;
			history.execute(*this, singleLine);
		}
		else if (singleLine[0] == 'B')
		{
			Borrow borrow;
			borrow.execute(*this, singleLine);
		}
		else if (singleLine[0] == 'R')
		{
			Return ret;
			ret.execute(*this, singleLine);
		}
		else
		{
			cout << "invalid character input" << endl;
		}
		cout << "1";
	}
}

void MovieStore::displayAllCustomerHistory() {
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

void MovieStore::displayCustomerHistory(int customerID)
{
	cout << "Customer ID: " << customerID << " ";

	//Convert Id to hash id
	customerID = hashCustomerID(customerID);

	cout << customerHashtable[customerID]->customer.firstName << " " << customerHashtable[customerID]->customer.lastName << endl;

	//Display the customers history, implimented in customer classF
	customerHashtable[customerID]->customer.displayHistory();
}

void MovieStore::displayInventory() {
	cout << "Comedy" << endl;
	cout << "Stock" << setw(14) << "Director" << setw(17) << "Title" << setw(35) << "Year \n";
	MovieHashNode *nodePtr = movieHashtable[1];
	while (nodePtr != NULL) {			
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
				<< setw(35) << nodePtr->movie->getTitle() << setw(20) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;

	cout << "Dramma" << endl;
	cout << internal << "Stock" << setw(14) << "Director" << setw(17) << "Title" << setw(35) << "Year \n";
	nodePtr = movieHashtable[2];
	while (nodePtr != NULL) {
		cout << left << setw(10) << nodePtr->stock << setw(20) << nodePtr->movie->getDirector()
			<< setw(35) << nodePtr->movie->getTitle() << setw(20) << nodePtr->movie->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;

	cout << "Classic" << endl;
	cout << internal << "Stock" << setw(14) << "Director" << setw(15) << "Title" << setw(35) << "Actor" << setw(17) << "Month" << setw(14) << "Year \n";
	nodePtr = movieHashtable[0];
	while (nodePtr != NULL) {
		Classic *classObj = static_cast<Classic*>(nodePtr->movie);
		cout << left << setw(10) << nodePtr->stock << setw(20) << classObj->getDirector()
			<< setw(35) << classObj->getTitle() << setw(20) << classObj->getActor() << 
			setw(20) << classObj->getMonth() << setw(20) << classObj->getYear() << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;
}

bool MovieStore::borrowMovie(string line)
{
	int	customerID = 0;
	char mediaType;
	string movieType= " ";
	string movieName = " ";
	string directorName;
	int movieYear = 0;
	int movieMonth = 0;
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
			movieName = movieName + line[counter];
			counter++; 
		}

		//Get the year of the movie
		movieYear = (line[counter + 2] - '0') * 1000;
		movieYear += (line[counter + 3] - '0') * 100;
		movieYear += (line[counter + 4] - '0') * 10;
		movieYear += line[counter + 5] - '0';

		MovieHashNode *currPtr = movieHashtable[1];
		//Loop until you have reahed the end of the movie linked list or found the movie you looking for


		while (currPtr != NULL)
		{
			//Check if title and year match up
			if (currPtr->movie->getTitle() == movieName && currPtr->movie->getYear() == movieYear)
			{
				//Check if there is still stock
				if (currPtr->stock > 0)
				{
					Movie *ptrForRef = currPtr->movie;
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canBorrow(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						currPtr->stock -= 1;
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
			}
			//If that wasnt the correct movie move on to the next one
			currPtr = currPtr->next;
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
					Movie *ptrForRef = NULL;
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
					Movie *ptrForRef = NULL;
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

bool MovieStore::returnMovie(string line) //////////////////////////////////////////////////////////////return
{
	int	customerID = 0;
	char mediaType;
	string movieType = " ";
	string movieName = " ";
	string directorName;
	int movieYear = 0;
	int movieMonth = 0;
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
			movieName = movieName + line[counter];
			//movieName[movieNameCounter] = line[counter];
			counter++; movieNameCounter++;
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
				//Check if the movies stock is full, if it is then no one has borrowed it yet so you cant return it
				if (movieHashtable[1]->stock == movieHashtable[1]->maxStock)
				{
					cout << "Cant return the item because you havent checked it out yet" << endl;
					return false;
				}
				else
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canReturn(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[1]->stock += 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear); /////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You have not borrowed this movie so you cant return it" << endl;
						return false;
					}
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
				//Check if the movies stock is full, if it is then no one has borrowed it yet so you cant return it
				if (movieHashtable[2]->stock == movieHashtable[2]->maxStock)
				{
					cout << "Cant return the item because you havent checked it out yet" << endl;
					return false;
				}
				else
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canReturn(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[2]->stock += 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear); /////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You have not borrowed this movie so you cant return it" << endl;
						return false;
					}
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
				//Check if the movies stock is full, if it is then no one has borrowed it yet so you cant return it
				if (movieHashtable[0]->stock == movieHashtable[0]->maxStock)
				{
					cout << "Cant return the item because you havent checked it out yet" << endl;
					return false;
				}
				else
				{
					//Checks if the customer is already borrowing this movie, and hasnt returned it yet
					if (customerHashtable[customerID]->customer.canReturn(customerID, movieType, action, movieName, directorName, movieMonth, movieYear) == true)
					{
						//If there is decriment it
						movieHashtable[0]->stock += 1;
						customerHashtable[customerID]->customer.addTransacionHistory(action, movieType, movieName, directorName, movieMonth, movieYear); /////////////////////////////////////////////////////ADD TO CUSTOMER HISTORY

						return true;
					}
					else
					{
						cout << "You have not borrowed this movie so you cant return it" << endl;
						return false;
					}
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
}
