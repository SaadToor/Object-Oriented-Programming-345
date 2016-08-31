#include <iostream>
#include "csvRead.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3){
	cerr << "Usage : " << argv[0] << "csv-file csv-seperator\n";
	return 1;
	}
	string filename = argv[1];
	char   seperator = argv[2][0];

	try {
		vector<vector<string>> csvData;
		csvdump(filename, seperator, csvData);
		csvprint(csvData);
	}
	catch (string& e) {
		cerr << e << "\n";
	}
	return 0;
}