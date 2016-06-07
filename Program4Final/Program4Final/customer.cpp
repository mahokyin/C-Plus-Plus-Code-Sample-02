#include "customer.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

Customer::Customer() {
	customerID = 0;
	firstName = "N/A";
	lastName = "N/A";
	head = NULL;
}

Customer::Customer(int id, string firstname, string lastname) {
	this->customerID = id;
	this->firstName = firstname;
	this->lastName = lastname;
	head = NULL;
}

Customer::~Customer() {
	// Delete linkedlist ptrs
	while (head != NULL) {
		HistoryData *oldNode = head;
		head = head->next;
		delete oldNode;
		oldNode = NULL;
	}
}

void Customer::addTransacionHistory(string transType, string genre, string title, string director, int month, int year)
{
	HistoryData *curr = head;
	HistoryData *newNode = new HistoryData;
	newNode->transactionType = transType;

	if (genre == "F") //////////////////////////Comedy
	{
		Comedy *comedy = new Comedy(title, director, year, "DVD");  /////////////////////NOT sure why its inaccessible
		newNode->movie = comedy;
		
													 //comedy->setDirector(director);
	}
	else if (genre == "D") //////////////////////////Drama
	{
		Drama *drama = new Drama(title, director, year, "DVD");
		newNode->movie = drama;
	}
	else if (genre == "C") //////////////////////////Classic
	{
		//Classic *drama = new Classic(title, director, year, "DVD", actor, month);
		//newNode->movie = drama;
	}

	while (curr->next != NULL)
	{
		curr = curr->next;
	}

	curr->next = newNode;
	newNode->next = NULL;
}

void Customer::displayHistory()
{

	HistoryData *curr = head;

	if (head == NULL) {
		cout << "No history for this customer" << endl;
		return;
	}

	while (curr != NULL)
	{
		cout << "DVD " << curr->transactionType << " ";

		Classic *classic = dynamic_cast<Classic*>(curr->movie);

		if (classic == NULL)
		{
			cout << curr->movie->getTitle() << " " << curr->movie->getDirector() << " " << curr->movie->getYear() << endl;
		}
		else
		{
			cout << classic->getTitle() << " " << classic->getDirector() << " " << classic->getYear() << " " << classic->getMonth() << " " << classic->getActor() << endl;
		}
	}
}

bool Customer::canBorrow(int id, string movieType, string action, string movieName, string directorName, int month, int year)
{
	HistoryData *curr = head;
	bool borrowNoReturn = false;

	if (movieType == "F") //////////////////////////////Comedy
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Comedy *comedy = dynamic_cast<Comedy*>(curr->movie);

			//Search through the history for the desired movie, if its been BORROWED
			if (curr->transactionType == action && comedy->getTitle() == movieName && comedy->getYear() == year)
			{
				//Found the movie in the customers history and they borrowed it, not sure if they returned it yet
				borrowNoReturn = true;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && comedy->getTitle() == movieName && comedy->getYear() == year)
			{
				//Found the movie in the customers history and they returned it
				borrowNoReturn = false;
			}

			//Traverse the list
			curr = curr->next;
		}
	}
	else if (movieType == "D") /////////////////////////////////Drama
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Drama *drama = dynamic_cast<Drama*>(curr->movie);

			//Search through the history for the desired movie, if its been BORROWED
			if (curr->transactionType == action && drama->getDirector() == directorName && drama->getTitle() == movieName)
			{
				//Found the movie in the customers history and they borrowed it, not sure if they returned it yet
				borrowNoReturn = true;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && drama->getDirector() == directorName && drama->getTitle() == movieName)
			{
				//Found the movie in the customers history and they returned it
				borrowNoReturn = false;
			}

			//Traverse the list
			curr = curr->next;
		}
	}
	else if (movieType == "C") //////////////////////////////////Classics
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Classic *classic = dynamic_cast<Classic*>(curr->movie);

			//Search through the history for the desired movie, if its been BORROWED
			if (curr->transactionType == action && classic->getDirector() == directorName && classic->getMonth() == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they borrowed it, not sure if they returned it yet
				borrowNoReturn = true;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && classic->getDirector() == directorName && classic->getMonth() == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they returned it
				borrowNoReturn = false;
			}

			//Traverse the list
			curr = curr->next;
		}
	}

	//Return depending on if the movie has been borrowed and not returned or not borrowed at all
	if (borrowNoReturn == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Customer::canReturn(int id, string movieType, string action, string movieName, string directorName, int month, int year)
{
	HistoryData *curr = head;
	bool borrowAndReturn = false; //Flag to check if movie was borrowed and returned

	if (movieType == "F") //////////////////////////////Comedy
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Comedy *comedy = dynamic_cast<Comedy*>(curr->movie);

			//Search through the history for the desired movie, if its been RETURNED
			if (curr->transactionType == action && comedy->getTitle() == movieName && comedy->getYear() == year)
			{
				//Found the movie in the customers history and they returned it
				borrowAndReturn = false;
			}
			//Search through the history for the desired movie, if its been BORROWED
			else if (curr->transactionType != action && comedy->getTitle() == movieName && comedy->getYear() == year)
			{
				//Found the movie in the customers history and they borrowed it
				borrowAndReturn = true;
			}

			//Traverse the list
			curr = curr->next;
		}
	}
	else if (movieType == "D") /////////////////////////////////Drama
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Drama *drama = dynamic_cast<Drama*>(curr->movie);

			//Search through the history for the desired movie, if its been BORROWED
			if (curr->transactionType == action && drama->getDirector() == directorName && drama->getTitle() == movieName)
			{
				//Found the movie in the customers history and they returned it
				borrowAndReturn = false;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && drama->getDirector() == directorName && drama->getTitle() == movieName)
			{
				//Found the movie in the customers history and they borrowed it
				borrowAndReturn = true;
			}

			//Traverse the list
			curr = curr->next;
		}
	}
	else if (movieType == "C") //////////////////////////////////Classics
	{
		//While youre not at the end of the list
		while (curr != NULL)
		{
			Classic *classic = dynamic_cast<Classic*>(curr->movie);

			//Search through the history for the desired movie, if its been BORROWED
			if (curr->transactionType == action && classic->getDirector() == directorName && classic->getMonth() == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they returned it
				borrowAndReturn = false;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && classic->getDirector() == directorName && classic->getMonth() == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they borrowed it
				borrowAndReturn = true;
			}

			//Traverse the list
			curr = curr->next;
		}
	}

	//Return depending on if the movie has been borrowed and not returned or not borrowed at all
	if (borrowAndReturn == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}