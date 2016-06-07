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
	void addTransacionHistory(string transType, string genre, string title, string director, int month, int year);
	void displayHistory();

	bool canBorrow(int id, string movieType, string action, string movieName, string directorName, int month, int year);
	bool canReturn(int id, string movieType, string action, string movieName, string directorName, int month, int year);
private:
	struct HistoryData
	{
		string transactionType = "";  //Either borrowed or retuned
		Movie *movie = NULL;				 //All the info about the particular movie
		HistoryData *next = NULL;
	};

	HistoryData *head = NULL;
};


#endif
