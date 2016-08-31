// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}


	Grades grades(argv[1]);
	// define the lambda expression for letter
	auto letter = [](double grade){
		std::string lGrade;
		if (grade >= 90)
			lGrade = "A+";
		else if (grade>80)
			lGrade = "A";
		else if (grade>75)
			lGrade = "B+";
		else if (grade>70)
			lGrade = "B";
		else if (grade>65)
			lGrade = "C+";
		else if (grade>60)
			lGrade = "C";
		else if (grade>55)
			lGrade = "D+";
		else if (grade>50)
			lGrade = "D";
		else
			lGrade = "F";
		return lGrade;
	};

	grades.displayGrades(std::cout, letter);


	std::cout << "Press any key to continue ... ";
	std::cin.get();
}