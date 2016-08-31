#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Product.h"

using namespace std;

namespace w7 {

	class Sale {
		vector<iProduct*> iProd;
		iProduct* ipr;
	public:
		Sale(const char* name);
		void display(std::ostream& os);
	};//sale class

}//namespace w7
