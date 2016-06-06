#include <iostream>
#include "moviestore.h"
using namespace std;

int main() {
	ifstream customerTextFile("data4customers.txt");
	ifstream movieTextFile("data4movies.txt");
	MovieStore movieStore(customerTextFile, movieTextFile);
	movieStore.displayAllCustomer();
	movieStore.displayAllMovie();
	system("pause");
	return 0;
}