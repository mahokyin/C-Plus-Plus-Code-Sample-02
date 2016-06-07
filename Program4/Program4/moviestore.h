#ifndef MOVIESTORE_H
#define MOVIESTORE_H
#include <iostream>
#include <string>
#include "movie.h"
#include "customer.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class MovieStore
{
public:
	MovieStore(); //creates a new instance of MovieStore that is empty.
	MovieStore(ifstream &inputCustomer, ifstream &inputMovie); //creates a new instance of MovieStore that is empty.

	bool readCustomerData(ifstream &input);
	bool readMovieData(ifstream &input);
	void readCommandData(ifstream &input);

    bool addCustomer(Customer &customer); //adds a new customer into the hash array of customers
        //using the line taken from the text document.
    bool addMovie(Movie *newMovie, int stockAmount); //adds a new movie into the movie double linked lsisted
        //using the line taken from the text document.

    void displayAllCustomerHistory();

	void displayCustomerHistory(int customerID);
    void displayInventory(); //takes the line that asks to print the inventory

    bool returnMovie(string line); //takes the line that asks to return a movie to the store
        //and returns it if the values are valid.
    bool borrowMovie(string line); //takes the line that asks to borrow a movie from the store
        //and borrows it if the values are valid.

private:
	// Structure of hashtable and hashNode for Customer object
	struct CustomerHashNode {
		Customer customer;
		CustomerHashNode *next = NULL;
	};
	CustomerHashNode *customerHashtable[10];
    int hashCustomerID(int id); // gets the hash value from the customer ID
								
	struct MovieHashNode {
		Movie *movie = NULL;
		int stock;
		int maxStock;
		MovieHashNode *next = NULL;
		MovieHashNode *prev = NULL;
	};
	MovieHashNode *movieHashtable[3];
	int hashMovieByObj(Movie *movie); // Hash function for movie hashtable and to return the hash value

	// Utility functions
	bool addClassic(Classic *newClassic, int stockAmount);
	bool addComedy(Comedy *newComedy, int stockAmount);
	bool addDrama(Drama *newDrama, int stockAmount);
	void addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead);
	void insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev);

};

#endif
