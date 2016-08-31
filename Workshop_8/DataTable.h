#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

namespace w8 {
	template<class T>

	class DataTable {
	private:
		int wid, dec;
		vector<T> x, y;
	public:
		DataTable(ifstream& is, int width, int decimal):wid(width),dec(decimal) {
			string line;
			size_t i = 0;
			while (getline(is,line)) {
				cout << "This is the line "<< line << endl;
				
				stringstream ssm;
				//Insert line into a stringstream
				ssm.str(line);
				
				T xX, yY;
				//Read into the variables created using Template T
				ssm >> xX >> yY;
				cout << "This is x: " << xX << endl 
					<< "This is y: " << yY << endl;

				//Storing all variables into vector(table) of x and y
				x.push_back(xX);
				cout << "This is variable X: " << x[i] << endl;
				y.push_back(yY);
				cout << "This is variable Y: " << y[i] << endl;
				i++;
			}
		}// Constructor

		T mean() const{
			return accumulate(y.begin(), y.end(), 0.0) / y.size();
		}
		T sigma() const {
			T meanValue = mean();
			T sum = 0.0;
			for (int i = 0; i < y.size(); i++)
				sum += (y[i] - meanValue) * (y[i] - meanValue);
			return sqrt(sum/(y.size()-1));
		}
		T median() const {
			vector<T> sorter = y;
			sort(sorter.begin(), sorter.end());
			return sorter[sorter.size() / 2];
		}
		void regression(T& slope, T& y_intercept) const{
			//Find the mean of x and y
			T averageX = accumulate(x.begin(), x.end(), 0.0) / x.size();
			T averageY = mean();

			T numerator = 0.0;
			T denomerator = 0.0;

			for (int i = 0; i < y.size(); i++) {
				numerator += (x[i] - averageX) * (y[i] - averageY);
				denomerator += (x[i] - averageX) * (x[i] - averageX);
			}
			slope = numerator / denomerator;
			y_intercept = averageY - (slope * averageX);
		}
		void display(ostream& os) const {
			os << setw(wid) << "x"
				<< setw(wid) << "y" << endl;
			for (int i = 0; i < x.size(); i++) 
				os << setw(wid) << fixed << setprecision(dec) << x[i]
					<< setw(wid) << fixed << setprecision(dec) << y[i] << endl;
		}
	};//Data Table class
	template<class T>
	ostream& operator<<(ostream& os, const DataTable<T>& d) {
		d.display(os);
		return os;
	}

}//W8 Namespace
