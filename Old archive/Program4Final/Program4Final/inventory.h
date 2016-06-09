//#include "transaction.h"
#include<iomanip>
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

using namespace std;

struct MovieHashNode {
	Movie *movie = NULL;
	int stock = 0;
	int maxStock = 0;
	MovieHashNode *next = NULL;
	MovieHashNode *prev = NULL;
};

class Inventory
{
public:
	// Default constructor
	Inventory();
	~Inventory();

	void displayInventory(); //takes the line that asks to print the inventory
	bool addMovie(Movie *newMovie, int stockAmount); //adds a new movie into the movie double linked lsisted

	MovieHashNode* searchInventory(Movie *movie);

private:
	MovieHashNode *movieHashtable[3];
	int hashMovieByObj(Movie *movie); // Hash function for movie hashtable and to return the hash value

	// Utility functions
	bool addClassic(Classic *newClassic, int stockAmount);
	bool addComedy(Comedy *newComedy, int stockAmount);
	bool addDrama(Drama *newDrama, int stockAmount);
	void addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead);
	void insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev);

};
