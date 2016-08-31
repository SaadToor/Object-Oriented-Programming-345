#include "csvRead.h"

void csvdump(string filename, char seperator, vector<vector<string>>& csvData) {
	ifstream is(filename);
	if (!is.is_open()) {
		throw string("Cannot open file' ") + filename + " '";
	}

	string line;
	while (getline(is, line)) {
		auto cr = line.find('\r');
		if (cr != string::npos) {
			line.erase(cr, 1);
		}
		cout << "-->" << line << "<--\n";

		string field;
		vector<string> columns;
		int index = 0;

		while (index < line.size()) {
			while (index < line.size() && line[index] != seperator) {
				field += line[index];
				index++;
			}
			index++;
			trimSpace(field);
			columns.push_back(field);
			cout << "field = '" << field << "'\n";
			field.clear();
		}
		csvData.push_back(columns);
		columns.clear();
	}

	is.close();
}
void trimSpace(string& f) {
	while (f.size() >  0 && f[0] == ' ') {
		f.erase(0, 1);
	}
	while (f.size() >  0 && f[f.size() - 1] == ' ') {
		f.erase(0, 1);
	}
}

void csvprint(vector<vector<string>>& csvData) {
	for (int row; row < csvData.size(); row++) {
		for (int col; col < csvData[row].size(); col++)
			cout << csvData[row][col];
		cout << endl;
	}
	cout << endl;
}
