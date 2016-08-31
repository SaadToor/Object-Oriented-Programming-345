#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Sale.h"

using namespace std;

namespace w7 {
	Sale::Sale(const char* name) {
		ifstream is(name);
		while (is.good()) {
			ipr = readProduct(is);
			iProd.push_back(ipr);
		}
	}

	void Sale::display(std::ostream& os) {
		double sum = 0;
		os << setw(10) << right << "Product No      "
			<< setw(10) << right << "Cost Taxable \n";
		os << fixed << setprecision(2);
		for (auto p : iProd) {
			os << *p;
			sum += p->getCharge();
		}
		os << std::setw(10) << std::right << "Total" << std::setw(10) << std::right << sum;
	}
}//namespace w7
