#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
	ifstream idTextFile("data4customers.txt");
	string str; 
	vector<string> vecId;
	vector<string> vecLastname;
	vector<string> vecFirstname;

	if (!idTextFile) cout << "error" << endl;
	// Need to add exception to handle the error if not found the file.

	while (getline(idTextFile, str)) {
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


	system("pause");
	return 0;
}