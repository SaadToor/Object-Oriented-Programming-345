#pragma once 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


namespace w3{
	class Text{
	private:
		size_t count;
		std::string* lineTable;

	public:
		size_t size()const;
		Text();
		Text(const char* filename);
		Text& operator= (const Text& rhs);
		Text&& operator= (Text&& rhs);
		Text(const Text& rhs);
		Text(Text&& rhs);
		~Text();


	};




} //namespace w3




