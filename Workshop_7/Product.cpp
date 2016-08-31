#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Product.h"

using namespace std;

namespace w7 {

		Product::Product(int productN, double cst) {
			prodNum = productN;
			cost = cst;
		}

		double Product::getCharge() const { 
			return cost; 
		}

		void Product::display(ostream& os) const {
			os << setw(10) << right << prodNum
				<< setw(10) << right << cost << endl;
		}

		TaxableProduct::TaxableProduct(int productN, double cst, char t) {
			prodNum = productN;
			cost = cst;
			tax = t;
		}

		double TaxableProduct::getCharge() const {
			double taxC = 1;
			if (tax == 'H')
				taxC = 1.13;
			if (tax == 'P')
				taxC = 1.08;
			return cost*taxC;
		}

		void TaxableProduct::display(ostream& os) const {
			os << setw(10) << right << prodNum
				<< setw(10) << right << cost << " ";
			if (tax == 'H') { os << setw(2) << right << "HST"; }
			if (tax == 'P') { os << setw(2) << right << "PST" << endl; }
			else { os << endl; }
		}

	ostream& operator<<(ostream& os, const iProduct& iP) {
		iP.display(os);
		return os;
	}

	iProduct* readProduct(ifstream& is) {
		int pNum;
		double cost;
		char t;
		iProduct* iprd;

		is >> pNum >> cost;
		if (is.get() != '\n') {
			is.get(t);
			iprd = new TaxableProduct(pNum, cost, t);
		}
		else {
			iprd = new Product(pNum, cost);
		}
		return iprd;
	}
}