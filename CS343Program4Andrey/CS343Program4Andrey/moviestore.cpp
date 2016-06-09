// ------------------------------------------------ moviestore.cpp -----------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - MovieStore functions that will read the files and break them up
// ---------------------------------------------------------------------------------------------------------------------
#include "moviestore.h"

using namespace std;

// ------------------------------------Default Constructor--------------------------------
MovieStore::MovieStore() {

}

// ---------------------------------------Constructor-------------------------------------
// Description: creates a new instance of MovieStore that is empty. Provides messages
//				for the success or failure of reading the files.
// PreCondition: Takes in 2 ifstream files, customer data and movie data
// ---------------------------------------------------------------------------------------
MovieStore::MovieStore(ifstream &inputCustomer, ifstream &inputMovie) {
	if (readCustomerData(inputCustomer)){
	}
	else cout << "Failure to read data !" << endl;
	if (readMovieData(inputMovie)){
	}
	else cout << "Failure to read data !" << endl;
	cout << endl;
}

// ----------------------------------readCustomerData ------------------------------------
// Description: Reads the customer file and breaks the file up, organizing the data
// preconditions: customer file must be saved in same folder as .h and .cpp files
// postconditions: customer object will be made for correct info from the file, or
//				   error message will be displayed.
// ---------------------------------------------------------------------------------------
bool MovieStore::readCustomerData(ifstream &input) {
	string str; //temp string
	if (!input) { //checks if file is valid
		cout << "File not found ! \n";
		return false;
	}

	while (getline(input, str)) { //Loop while not at eof
		string id; string lastname; string firstname;

		istringstream stream(str); //Convert string to istringstream
		stream >> id >> lastname >> firstname;
		int intId = 0; istringstream(id) >> intId;

		//make a new customer with data from file
		Customer *customer = new Customer(intId, firstname, lastname);
		history.addCustomer(customer);
	}
	return true;
}

// -----------------------------------readMovieData --------------------------------------
// Description: Reads the movie file and breaks the file up, organizing the data
// preconditions: movie file must be saved in same folder as .h and .cpp files
// postconditions: movie object will be made for correct info from the file, or
//				   error message will be displayed.
// ---------------------------------------------------------------------------------------
bool MovieStore::readMovieData(ifstream &input) {
	string str; //temp string
	if (!input) { //checks if file is valid
		cout << "File not found ! \n";
		return false;
	}

	while (getline(input, str, ',')) { //Loop while not at eof
		string type;
		istringstream stream(str); //Convert string
		stream >> type;

		//Checks which genre depending on first char from file
		if (type == "F" || type == "D") {
			string stock, director, title, year; //Declare variables

			//Reads in data using getline
			getline(input, stock, ',');
			getline(input, director, ',');
			director = director.substr(1, director.size());
			getline(input, title, ',');
			title = title.substr(1, title.size());
			getline(input, year, '\n');
			int intYear, intStock;
			istringstream stream(year);
			stream >> intYear; istringstream stockStream(stock); stockStream >> intStock;

			//Checks the genre, makes a new movie depending on which one
			if (type == "F") inventory.addMovie(new Comedy(director, title, intYear, "F"), intStock);
			else inventory.addMovie(new Drama(director, title, intYear, "D"), intStock);
		}
		else if (type == "C") {
			//Declare variables
			string stock, director, title, year, actorFirstname, actorLastname, day;

			//Uses getline to read in the info and organize
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

			//Create new classic movie
			inventory.addMovie(new Classic(director, title, intYear, "C", actorFirstname + " " + actorLastname, intDay), intStock);
		}
		else getline(input, str, '\n');
	}
	return true;
}

// -----------------------------------readCommandData ------------------------------------
// Description: Reads the command file and breaks the file up, organizing the data
// preconditions: command file must be saved in same folder as .h and .cpp files
// postconditions: One of 4 actions will be performed (Borrow, Return, History, Inventory)
//				   or error message will be displayed.
// ---------------------------------------------------------------------------------------
void MovieStore::readCommandData(ifstream &input) {
	string str; //temp string
	if (!input) { //checks if file is valid
		cout << "File not found ! \n";
	}

	string singleLine;

	//Loop while not at the end of the file
	while (!input.eof())
	{
		//Gets a line from the data file and saves it into variable "singleLine"
		getline(input, singleLine);

		//Calls different function depending on the action given from the file
		if (singleLine[0] == 'I') { //Inventory
			inventory.displayInventory();
		} 
		else if (singleLine[0] == 'H') //Customer history
		{
			int custID = 0;
			char temp;
			istringstream stream(singleLine); stream >> temp >> custID;
			history.displayCustomerHistory(custID);
		}
		else if (singleLine[0] == 'B' || singleLine[0] == 'R') //Borrow or return
		{
			//Declare variables
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

			if (movieType == "F") //Comedy
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

				//Currently only have DVD
				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				}
				else { 
					Comedy comedy("N/A", movieName, movieYearInt, movieType);
					if (action == "B") { //make a new comedy, and borrow objects for this movie
						Borrow borrow(inventory, history, customerID, comedy);
						borrow.execute();
					}
					else { //make a new comedy, and return objects for this movie
						Return returnM(inventory, history, customerID, comedy);
						returnM.execute();
					}
				}
			}
			else if (movieType == "D") //Drama
			{
				counter = 11; //Keeps track of where on the line you are
				while (singleLine[counter] != ',') //Get director name
				{
					directorName = directorName + singleLine[counter];
					counter++;
				}
				counter += 2;

				while (singleLine[counter] != ',') //get movie name
				{ 
					movieName = movieName + singleLine[counter];
					counter++;
				}
				movieName = movieName.substr(1, movieName.size()); //get rid of space in front of name

				//Currently only have DVD
				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				}
				else {
					Drama drama(directorName, movieName, 0, movieType);
					if (action == "B") { //make a new drama, and borrow objects for this movie
						Borrow borrow(inventory, history, customerID, drama);
						borrow.execute();
					}
					else { //make a new drama, and return objects for this movie
						Return returnM(inventory, history, customerID, drama);
						returnM.execute();
					}
				}
			}
			else if (movieType == "C") //classic
			{
				counter = 11;
				monthMovieInt = 0;

				//Get month of the movie
				monthMovieInt = singleLine[counter] - '0';
				counter++;

				if (singleLine[counter] != ' ')
				{
					monthMovieInt = (monthMovieInt * 10) + (singleLine[counter] - '0');
					counter++;
				}
				counter += 1;

				//Get the year of the movie
				movieYearInt = (singleLine[counter] - '0') * 1000;
				movieYearInt += (singleLine[++counter] - '0') * 100;
				movieYearInt += (singleLine[++counter] - '0') * 10;
				movieYearInt += singleLine[++counter] - '0';
				counter += 2;

				//Actors first name
				while (singleLine[counter] != ' ')
				{
					string temp(1, singleLine[counter]);
					actorFirst = actorFirst + temp;
					counter++;
				}
				counter += 1;

				//Actors last name
				while (counter < singleLine.size())
				{
					actorLast = actorLast + singleLine[counter];
					counter++;
				}

				if (actorLast[actorLast.size() - 1] == '\r')
					actorLast.erase(actorLast.size() - 1);

				//only DVD at the moment
				if (mediaType != 'D') {
					cout << "Invalid Action: Invalid media type !" << endl;
				} 
				else { //make a new classic and borrow objects
					Classic classic("N/A", "N/A", movieYearInt, movieType, actorFirst + " " + actorLast, monthMovieInt);
					if (action == "B") {
						Borrow borrow(inventory, history, customerID, classic);
						borrow.execute();
					}
					else { //make a new classic and return objects
						Return returnM(inventory, history, customerID, classic);
						returnM.execute();
					}
				}
			}
		}
		else { //Not one of the 4 actions
			cout << "invalid character input" << endl;
		}
	}
}


