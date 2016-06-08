#include "moviestore.h"

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
		istringstream stream(str);
		stream >> id >> lastname >> firstname;
		int intId = 0; istringstream(id) >> intId;
		Customer *customer = new Customer(intId, firstname, lastname);
		//Customer customer(intId, firstname, lastname);
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
		istringstream stream(str);
		stream >> type;
		if (type == "F" || type == "D") {
			string stock, director, title, year;
			getline(input, stock, ',');
			getline(input, director, ',');
			director = director.substr(1, director.size());
			getline(input, title, ',');
			title = title.substr(1, title.size());
			getline(input, year, '\n');
			int intYear, intStock;
			istringstream stream(year);
			stream >> intYear; istringstream stockStream(stock); stockStream >> intStock;
			if (type == "F") inventory.addMovie(new Comedy(director, title, intYear, "F"), intStock);
			else inventory.addMovie(new Drama(director, title, intYear, "D"), intStock);
		}
		else if (type == "C") {
			string stock, director, title, year, actorFirstname, actorLastname, day;
			getline(input, stock, ',');
			getline(input, director, ',');
			director = director.substr(1, director.size());
			getline(input, title, ',');
			title = title.substr(1, title.size());
			getline(input, str);
			istringstream stream(str);
			stream >> actorFirstname >> actorLastname >> day >> year;
			int intYear, intStock, intDay;
			istringstream stream2(year); stream2 >> intYear; istringstream(stock) >> intStock; istringstream(day) >> intDay;
			inventory.addMovie(new Classic(director, title, intYear, "C", actorFirstname + " " + actorLastname, intDay), intStock);
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
		} 
		else if (singleLine[0] == 'H')
		{
			int custID = 0;
			char temp;
			istringstream stream(singleLine); stream >> temp >> custID;
			history.displayCustomerHistory(custID);
		}
		else if (singleLine[0] == 'B' || singleLine[0] == 'R')
		{
			int	customerID = 0;
			char mediaType;
			string movieType = " ";
			string movieName = " ";
			string directorName;
			int movieYearInt = 0;
			int monthMovieInt = 0;
			int counter = 11;
			int movieNameCounter = 0;
			string action(1, singleLine[0]); //For borrow, will be 'r' for return, used for helper function canBorrow

			string actorFirst;
			string actorLast;
			string actorFull;

			string temp;

			//Get the customer id
			customerID = (singleLine[2] - '0') * 1000;
			customerID += (singleLine[3] - '0') * 100;
			customerID += (singleLine[4] - '0') * 10;
			customerID += singleLine[5] - '0';

			mediaType = singleLine[7];

			movieType[0] = singleLine[9];

			if (movieType == "F")
			{
				//Get the name of the movie
				while (singleLine[counter] != ',')
				{
					movieName = movieName + singleLine[counter];
					counter++;
				}

				//Get the year of the movie
				movieYearInt = (singleLine[counter + 2] - '0') * 1000;
				movieYearInt += (singleLine[counter + 3] - '0') * 100;
				movieYearInt += (singleLine[counter + 4] - '0') * 10;
				movieYearInt += singleLine[counter + 5] - '0';

				movieName = movieName.substr(1, movieName.size());

				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				}
				else {
					Comedy comedy("N/A", movieName, movieYearInt, movieType);
					if (action == "B") {
						Borrow borrow(inventory, history, customerID, comedy);
						borrow.execute();
					}
					else {
						Return returnM(inventory, history, customerID, comedy);
						returnM.execute();
					}
				}
				//cout << action << " " << customerID << " " << mediaType << " " << movieType << " " << movieName << " " << movieYearInt << endl;
			}
			else if (movieType == "D")
			{
				counter = 11;

				while (singleLine[counter] != ',')
				{
					directorName = directorName + singleLine[counter];
					counter++;
				}
				counter += 2;

				while (singleLine[counter] != ',')
				{
					movieName = movieName + singleLine[counter];
					counter++;
				}
				movieName = movieName.substr(1, movieName.size());


				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				}
				else {
					Drama drama(directorName, movieName, 0, movieType);
					if (action == "B") {
						Borrow borrow(inventory, history, customerID, drama);
						borrow.execute();
					}
					else {
						Return returnM(inventory, history, customerID, drama);
						returnM.execute();
					}
				}

				//cout << action << " " << customerID << " " << mediaType << " " << movieType << " " << directorName << " " << movieName << endl;
			}
			else if (movieType == "C")
			{
				counter = 11;
				monthMovieInt = 0;

				monthMovieInt = singleLine[counter] - '0';
				counter++;

				if (singleLine[counter] != ' ')
				{
					monthMovieInt = (monthMovieInt * 10) + (singleLine[counter] - '0');
					counter++;
				}
				counter += 1;
				//convert month to int

				//Get the year of the movie
				movieYearInt = (singleLine[counter] - '0') * 1000;
				movieYearInt += (singleLine[++counter] - '0') * 100;
				movieYearInt += (singleLine[++counter] - '0') * 10;
				movieYearInt += singleLine[++counter] - '0';

				counter += 2;

				while (singleLine[counter] != ' ')
				{
					string temp(1, singleLine[counter]);
					actorFirst = actorFirst + temp;
					counter++;
				}
				counter += 1;

				while (counter < singleLine.size())
				{
					actorLast = actorLast + singleLine[counter];
					counter++;
				}

				if (actorLast[actorLast.size() - 1] == '\r')
					actorLast.erase(actorLast.size() - 1);

				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				}
				else {
					Classic classic("N/A", "N/A", movieYearInt, movieType, actorFirst + " " + actorLast, monthMovieInt);
					if (action == "B") {
						Borrow borrow(inventory, history, customerID, classic);
						borrow.execute();
					}
					else {
						Return returnM(inventory, history, customerID, classic);
						returnM.execute();
					}
				}
				//cout << action << " " << customerID << " " << mediaType << " " << movieType << " " << monthMovieInt << " " << movieYearInt << " " << actorFirst << " " << actorLast << endl;
			}
		}
		else {
			cout << "invalid character input" << endl;
		}
	}
}


