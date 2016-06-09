#include <iostream>
#include "moviestore.h"
using namespace std;

int main() {
	ifstream customerTextFile("data4customers.txt");
	ifstream movieTextFile("data4movies.txt");
	MovieStore movieStore(customerTextFile, movieTextFile);

	ifstream movieCommandFile("data4commands.txt");
	movieStore.readCommandData(movieCommandFile);

	//system("pause");
	return 0;
}