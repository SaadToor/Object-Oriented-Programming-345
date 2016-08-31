#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "util.h"
// using namespace std;

std::string& trim(std::string& s, char trimChar) {
	while (!s.empty() && s[0] == trimChar)
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == trimChar)
		s.erase(s.size() - 1, 1);

	return s;
}

void csvprint(std::vector<std::vector<std::string>>& csvData) {
	for (int row = 0; row < csvData.size(); row++) {
		for (int col; col < csvData[row].size(); col++)
			std::cout << csvData[row][col];
		std::cout << std::endl;
	}
}

#define PROCESS_DOUBLE_QUOTES
void csvReader(std::string& filename, char delim, std::vector< std::vector<std::string> >& csv) {
	std::ifstream is(filename);
	if (is) {
		std::string line;
		std::vector<std::string> fields;

		while (getline(is, line)) {
			auto cr = line.find('\r');
			if (cr != std::string::npos) line.erase(cr, 1);
			auto nl = line.find('\n');
			if (nl != std::string::npos) line.erase(cr, 1);


			std::string field;
			for (size_t i = 0; i < line.size(); i++) {
				trim(line);
				if ((line[i] != delim && line[i] != ',') && line[i] != '\0') {
					field += line[i];
				}
				else {
					trim(field);
					fields.push_back(field);
					field.clear();
				}
			}
			if (!field.empty()) {
				trim(field);
				fields.push_back(field);
				csv.push_back(fields);
				fields.clear();
			}
		}
		is.close();
	}
	else {
		std::cerr << "cannot open file " << filename << "\n";
	}
}
