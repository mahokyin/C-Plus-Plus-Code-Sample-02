#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include "movie.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"

using namespace std;

class Customer
{
public:
	Customer();
	Customer(int, string, string);
	~Customer();

	int customerID;
	string firstName;
	string lastName;

	//Function is used to save the transaction to the HistoryData linked list
	void addTransacionHistory(string trans, Movie *movie);
	void displayHistory();

	bool canBorrow(string transType, Movie *movie);
	bool canReturn(string transType, Movie *movie, string *errorMsg);

private:
	struct HistoryData
	{
		string transactionType;  //Either borrowed or retuned
		Movie *movie = NULL;				 //All the info about the particular movie
		HistoryData *next = NULL;
	};

	HistoryData *head = NULL;
};


#endif
