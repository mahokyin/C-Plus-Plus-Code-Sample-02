#ifndef MOVIESTORE_H
#define MOVIESTORE_H
#include <iostream>
#include <string>
#include "movie.h"
//#include "customer.h"

using namespace std;

class MovieStore
{
public:
	MovieStore(); //creates a new instance of MovieStore that is empty.
	//void addCustomer(Customer newCustomer); //adds a new customer into the hash array of customers
	//using the line taken from the text document.
	void addMovie(Movie *Movie, int stock); //adds a new movie into the movie double linked lsisted
	//using the line taken from the text document.
	void displayCustomerHistory(string line); //takes the line that asks to print the information
	//of the transactions of a user, and prints it.
	void displayInventory(string line); //takes the line that asks to print the inventory
	//of the movie store, and prints it.
	bool returnMovie(string line); //takes the line that asks to return a movie to the store
	//and returns it if the values are valid.
	bool borrowMovie(string line); //takes the line that asks to borrow a movie from the store
	//and borrows it if the values are valid.

	void readMovieData(ifstream &input);

private:
	void expandCustomerArray(); //this method is used to expand the Customer array in case
	//it is too full to add a new customer.
	//Customers[] customers; // a hash array that contains the customers in the movie store.
	void hashCustomerID(int id); // gets the hash value from the customer ID
	struct movieNode { //struct to store the information about the movies
		Movie *m;
		int stock;
		int maxStock;
		movieNode *next = NULL;
	};
	struct movieHead {  // struct to store the information about the different genres, and
		//holds the head of the movieNode of that genre.
		string genre;
		movieHead *nextGenre = NULL; //down pointer
		movieNode *first = NULL;	  //right pointer
	};
	movieHead *head = NULL; // holds all the information about the movies in the store. can be viewed as
	// linked list of linked lists.


};

#endif
