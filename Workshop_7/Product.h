#ifndef _I_PRODUCT_H_
#define _I_PRODUCT_H_

// Workshop 7 - STL Containers
// iProduct.h

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

namespace w7 {

	class iProduct {
	public:
		virtual double getCharge() const = 0;
		virtual void display(ostream&) const = 0;
	};//iProduct class

	class Product :public iProduct {
		int prodNum;
		double cost;
	public:
		Product(int productN, double cst);
		double getCharge() const;
		void display(ostream& os) const;
	};//Product derived from iProduct class

	class TaxableProduct :public iProduct {
		int prodNum;
		double cost;
		char tax;
	public:
		TaxableProduct(int productN, double cst, char t);
		double getCharge() const;
		void display(ostream& os) const;
	};//TaxableProduct derived from iProduct class

	ostream& operator<<(ostream& os, const iProduct& iP);
	iProduct* readProduct(ifstream& is);
}
#endif