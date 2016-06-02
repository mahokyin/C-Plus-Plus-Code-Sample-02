#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool readCustomerData(ifstream &input) {
	string str;
	vector<string> vecId;
	vector<string> vecLastname;
	vector<string> vecFirstname;

	if (!input) return false;
	// Need to add exception to handle the error if not found the file.

	while (getline(input, str)) {
		string id; string lastname; string firstname;
		istringstream(str) >> id >> lastname >> firstname;
		vecId.push_back(id);
		vecLastname.push_back(lastname);
		vecFirstname.push_back(firstname);
	}

	for (int i = 0; i < vecId.size(); i++) {
		cout << vecId[i] << "\t" <<
			vecLastname[i] << "\t" <<
			vecFirstname[i] << endl;
	}

	return true;
}

int main() {
	ifstream idTextFile("data4customers.txt");
	readCustomerData(idTextFile);


	system("pause");
	return 0;
}

