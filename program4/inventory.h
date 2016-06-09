// ------------------------------------------------ inventory.h --------------------------------------------------------
// Programmer Name: Joe Ma, Andrey Spencer
// Assignment: Program 4 implementation
// Creation Date: 6/1/16
// Date of Last Modification: 6/8/16
// ---------------------------------------------------------------------------------------------------------------------
// Purpose - This header containes Inventory class that deals with adding, displaying, and searching the inventory of 
//			 the store. Also contains MovieHashNode, a struct that holders all the data nessesary for a movie node.
// ---------------------------------------------------------------------------------------------------------------------
#include<iomanip>
#include "movie.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"

using namespace std;

//Movie Node Struct
//Stored data used in each node of the movie linked list
struct MovieHashNode {
	Movie *movie = NULL; //Movie data
	int stock;			 //Stock
	MovieHashNode *next = NULL; //Next pointer
	MovieHashNode *prev = NULL; //Pevious pointer
}; 

class Inventory
{
public:
	// ---------------------------------------Constructor-------------------------------------
	// Description: Initializes the movie hash table.
	// ---------------------------------------------------------------------------------------
	Inventory();

	// ---------------------------------------Destructor--------------------------------------
	// Description: Deletes all the memory allocated in inventory.cpp.
	// PostCondition: All memory will be released.
	// ---------------------------------------------------------------------------------------
	~Inventory();

	// ----------------------------------displayInventory-------------------------------------
	// Description: Displays all the movies in the store, by running through the hash table.
	// PreCondition: Contructor must be implimented.
	// PostCondition: All movies will be displayed.
	// ---------------------------------------------------------------------------------------
	void displayInventory(); 

	// -------------------------------------addMovie-----------------------------------------
	// Description: Creates a new movie Node, calls a helper function to insert the node into
	//			    the correct location in the hashTables linked list.
	// PreCondition: Hash table needs to be created. Takes in the movie and stock amount.
	// PostCondition: Whichever genres the movie is, that ones helper function will be called.
	// ---------------------------------------------------------------------------------------
	bool addMovie(Movie *newMovie, int stockAmount); 

	// --------------------------------searchInventory----------------------------------------
	// Description: Search through the inventory hash table for the movie provided.
	// PreCondition: Must recieve the movie that is being searched for
	// PostCondition: Returns a pointer to the node of the movie if found, else return null.
	// ---------------------------------------------------------------------------------------
	MovieHashNode* searchInventory(Movie *movie);
private:
	MovieHashNode *movieHashtable[3]; //Hash Table

	// ------------------------------------hashMovieByObj-------------------------------------
	// Description: Hashes the movies by the genre.
	// PreCondition: Contructor must be implimented. Takes in the movie to check the type.
	// PostCondition: return the hash value depending on the genre.
	// ---------------------------------------------------------------------------------------
	int hashMovieByObj(Movie *movie); 

	// -------------------------------------addClassic----------------------------------------
	// Description: Inserts the new classic movie into the hash table and inserts it into the
	//				correct location in the linked list.
	// PreCondition: Hash table needs to be created. takes in the classic movie and stock amount.
	// PostCondition: Classic movie is inserted into correct location of linked list.
	// ---------------------------------------------------------------------------------------
	bool addClassic(Classic *newClassic, int stockAmount);

	// -------------------------------------addComedy-----------------------------------------
	// Description: Inserts the new comedy movie into the hash table and inserts it into the
	//				correct location in the linked list.
	// PreCondition: Hash table needs to be created. takes in the comedy and stock amount.
	// PostCondition: Comedy movie is inserted into correct location of linked list.
	// ---------------------------------------------------------------------------------------
	bool addComedy(Comedy *newComedy, int stockAmount);

	// -------------------------------------addDrama------------------------------------------
	// Description: Inserts the new drama movie into the hash table and inserts it into the
	//				correct location in the linked list.
	// PreCondition: Hash table needs to be created. takes in the drama movie and stock amount.
	// PostCondition: Drama movie is inserted into correct location of linked list.
	// ---------------------------------------------------------------------------------------
	bool addDrama(Drama *newDrama, int stockAmount);

	// ------------------------------addFirstMovieNode----------------------------------------
	// Description: Inserts the new movie into the first location in the linked list.
	// PreCondition: Must recieve the correct movie, stock, and prev pointer, head, and index.
	// PostCondition: The movie will be inserted into the linked list.
	// ---------------------------------------------------------------------------------------
	void addFirstMovieNode(Movie *movie, int stockAmount, int index, MovieHashNode *oldHead);

	// --------------------------------insertMovieNode----------------------------------------
	// Description: Inserts the new movie into the correct location in the linked list.
	// PreCondition: Must recieve the correct movie, stock, and prev pointer.
	// PostCondition: The movie will be inserted into the linked list.
	// ---------------------------------------------------------------------------------------
	void insertMovieNode(Movie *movie, int stockAmount, MovieHashNode *prev);
};
