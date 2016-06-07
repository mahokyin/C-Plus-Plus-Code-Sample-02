#include "moviestore.h"
#include <stdlib.h>
#include <cstdlib>
#include<iomanip>
using namespace std;

MovieStore::MovieStore() {

}

MovieStore::MovieStore(ifstream &inputCustomer, ifstream &inputMovie) {
	if(readCustomerData(inputCustomer)) cout << "Succesful read customer data !" << endl;
	else cout << "Failure to read data !" << endl;
	if (readMovieData(inputMovie)) cout << "Succesfull read movie data !" << endl;
	else cout << "Failure to read data !" << endl;
	cout << endl;
}

bool MovieStore::readCustomerData(ifstream &input) {
	string str;
	if (!input) {
		cout << "File not found ! \n";
		return false;
	}
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str)) {
		string id; string lastname; string firstname;
		istringstream(str) >> id >> lastname >> firstname;
		int intId = 0; istringstream(id) >> intId;
		Customer customer(intId, firstname, lastname);
		history.addCustomer(customer);
	}
	return true;
}

bool MovieStore::readMovieData(ifstream &input) {
	string str;
	if (!input) {
		cout << "File not found ! \n";
		return false;
	}
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str, ',')) {
		string type;
		istringstream(str) >> type;
		if (type == "F" || type == "D") {
			string stock, director, title, year;
			getline(input, stock, ',');
			getline(input, director, ',');
			director = director.substr(1, director.size());
			getline(input, title, ',');
			title = title.substr(1, director.size());
			getline(input, year, '\n');
			int intYear, intStock; istringstream(year) >> intYear; istringstream(stock) >> intStock;
			if (type == "F") inventory.addMovie(new Comedy(director, title, intYear, "F"), intStock);
			else inventory.addMovie(new Drama(director, title, intYear, "D"), intStock);
		}
		else if (type == "C") {
			string stock, director, title, year, actorFirstname, actorLastname, day;
			getline(input, stock, ',');
			getline(input, director, ',');
			director = director.substr(1, director.size());
			getline(input, title, ',');
			title = title.substr(1, director.size());
			getline(input, str);
			istringstream(str) >> actorFirstname >> actorLastname >> day >> year;
			int intYear, intStock, intDay;
			istringstream(year) >> intYear; istringstream(stock) >> intStock; istringstream(day) >> intDay;
			inventory.addMovie(new Classic(director, title, intYear, "F", actorFirstname + " " + actorLastname, intDay), intStock);
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
			inventory.displayInventory();
			cout << "1" << endl;
		} 
		else if (singleLine[0] == 'H')
		{
			//History history;
			//history.execute(*this, singleLine);
		}
		else if (singleLine[0] == 'B')
		{
			//Borrow borrow;
			//borrow.execute(*this, singleLine);
		}
		else if (singleLine[0] == 'R')
		{
			//Return ret;
			//ret.execute(*this, singleLine);
		}
		else {
			cout << "invalid character input" << endl;
		}
	}
}

void MovieStore::displayAllCustomerHistory() {
	history.displayAllCustomerHistory();
}

/*
void MovieStore::displayCustomerHistory(int customerID)
{
	cout << "Customer ID: " << customerID << " ";

	//Convert Id to hash id
	customerID = hashCustomerID(customerID);

	cout << customerHashtable[customerID]->customer.firstName << " " << customerHashtable[customerID]->customer.lastName << endl;

	//Display the customers history, implimented in customer classF
	customerHashtable[customerID]->customer.displayHistory();
}
 */

void MovieStore::displayInventory() {
	inventory.displayInventory();
}


