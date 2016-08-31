#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class Grades {
	string* name;
	size_t sz;
	size_t counter;
	int* value;
	double* grade;
public:
	Grades(const char* nm){
		counter = 0;
		name = new string[strlen(nm)];
		value = new int[250];
		grade = new double[250];
		for (int i = 0; i < strlen(nm); name[i++] = nm[i++]);
		int i = 0;
		ifstream is(nm);
		if (is.is_open()) {
			string line;
			while (getline(is, line)) {
				cout << i << ": " << line << endl;

				value[i] = stoi(line, &sz);
				grade[i] = stod(line.substr(sz));

				cout << "this is the value: " << value[i] << endl;
				cout << "this is the grade: " << grade[i] << endl;

				i++;
				counter++;
			}
		}
		else {
			cerr << "There is no file named: " << nm << endl;
			exit(1);
		}
		is.close();
	}
	template<typename T>
	void displayGrades(ostream& os, T letter) const{
		for (int i = 0; i < counter; i++)
			os << value[i] << " " << grade[i] << " " << letter(grade[i]) << endl;
	}

};//Grades class
