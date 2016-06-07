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
		Comedy *comedy = dynamic_cast<Comedy*>(newNode->movie);  /////////////////////NOT sure why its inaccessible
		//comedy->setDirector(director);
		comedy->setMovieGenre(genre);
		comedy->setMovieTitle(title);
		comedy->setMovieYear(year);
	}
	else if (genre == "D") //////////////////////////Drama
	{
		Drama *drama = dynamic_cast<Drama*>(newNode->movie);  /////////////////////NOT sure why its inaccessible
		drama->setDirector(director);
		drama->setMovieGenre(genre);
		drama->setMovieTitle(title);
		//drama->setMovieYear(year);
	}
	else if (genre == "C") //////////////////////////Classic
	{
		Classic *classic = dynamic_cast<Classic*>(newNode->movie);  /////////////////////NOT sure why its inaccessible
		classic->setDirector(director);
		classic->setMovieGenre(genre);
		//classic->setMovieTitle(title);
		classic->setMovieYear(year);
		classic->setMonth(month);
		//classic->setActor(actor);
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

	while (curr != NULL)
	{
		cout << "DVD " << curr->transactionType << " ";

		if (curr->movie->getType() == "F")
		{
			Comedy *comedy = dynamic_cast<Comedy*>(curr->movie);
			cout << comedy->getTitle() << " " << comedy->getDirector() << " " << comedy->getYear() << endl;
		}
		else if (curr->movie->getType() == "D")
		{
			Drama *drama = dynamic_cast<Drama*>(curr->movie);
			cout << drama->getTitle() << " " << drama->getDirector() << " " << drama->getYear() << endl;
		}
		else if (curr->movie->getType() == "C")
		{
			Classic *classic = dynamic_cast<Classic*>(curr->movie);
			cout << classic->getTitle() << " " << classic->getDirector() << " " << classic->getYear() << " " << classic->getDay() << " " << classic->getActor() << endl;
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
			if (curr->transactionType == action && classic->getDirector() == directorName && classic->getDay == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they borrowed it, not sure if they returned it yet
				borrowNoReturn = true;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && classic->getDirector() == directorName && classic->getDay == month && classic->getYear() == year)
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
			if (curr->transactionType == action && classic->getDirector() == directorName && classic->getDay == month && classic->getYear() == year)
			{
				//Found the movie in the customers history and they returned it
				borrowAndReturn = false;
			}
			//Search through the history for the desired movie, if its been RETURNED
			else if (curr->transactionType != action && classic->getDirector() == directorName && classic->getDay == month && classic->getYear() == year)
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