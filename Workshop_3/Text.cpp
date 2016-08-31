#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Text.h"

using namespace std;

namespace w3{

		size_t Text::size()const{
			return count;
		}

		Text::Text() :count(0), lineTable(nullptr){}

		Text::Text(const char* filename) :count(0){
			ifstream is(filename);
			if (is.is_open()){
				string line;
				// count the number of lines in the file
				count = 0;
				while (getline(is, line))
					count++;
				cout << "File '" << filename << "; contains " << count << "lines. \n";

				lineTable = new string[count];

				is.clear(); //clear EOF(end of file) error state
				is.seekg(0);

				for (size_t line = 0; line < count; line++){
					getline(is, lineTable[line]);
					auto cr = lineTable[line].find('\r');
					if (cr != string::npos)
						lineTable[line].erase(cr);
				}
				size_t lines = (count < 10 ? count : 10);
				for (size_t line = 0; line < lines; line++){
					cout << line << "; -->" << lineTable[line] << "<--\n";
				}
				is.close();
			}
			else{
				cerr << "cannot open file '" << filename << "'.\n";
				exit(3);
			}
		}

		Text& Text::operator= (const Text& rhs)  { // c++ assignment operator
			if (this != &rhs){
				//if we have a lineTable, delete it
				if (lineTable){
					delete[] lineTable;
					lineTable = nullptr;
					count = 0;
					// we are now a zombie
				}
				// deep copy rhs
				if (rhs.lineTable){
					count = rhs.count;
					lineTable = new string[count];
					for (size_t line = 0; line < count; line++){
						lineTable[line] = rhs.lineTable[line];
					}
				}
			}
			return *this;
		}

		Text&& Text::operator= (Text&& rhs)  {  // c++11 move assignment operator
			if (this != &rhs){
				//if we have a lineTable, delete it
				if (lineTable){
					delete[] lineTable;
					lineTable = nullptr;
					count = 0;
					// we are now a zombie
				}

				// move pointer+count
				count = rhs.count;
				lineTable = rhs.lineTable;
				//turn rhs into a zombie 
				rhs.count = 0;
				rhs.lineTable = nullptr;

			}
			return std::move(*this);
		}

		Text::Text(const Text& rhs){  // c++ copy constructor

			count = 0;
			lineTable = nullptr;
			*this = rhs; // let the assignemt operator do the work 

		}

		Text::Text(Text&& rhs) {  // c++11 move constructor

			count = 0;
			lineTable = nullptr;
			*this = std::move(rhs);  // let the assignemt operator do the work

		}

		Text::~Text(){
			delete[] lineTable;
		}


} //namespace w3
