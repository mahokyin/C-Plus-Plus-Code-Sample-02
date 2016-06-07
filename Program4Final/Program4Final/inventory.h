//#include "transaction.h"
#include<iomanip>
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

using namespace std;

class Inventory
{
public:
	// Default constructor
	Inventory();

	void displayInventory(); //takes the line that asks to print the inventory
	bool addMovie(Movie *newMovie, int stockAmount); //adds a new movie into the movie double linked lsisted

private:
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
