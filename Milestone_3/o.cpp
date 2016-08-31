#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
#include "o.h"

using namespace std;

bool Order::isCustomerName(std::string& s) {
	return((!s.empty()) && isalpha(s[0]));
}
bool Order::isProductName(std::string& s) {
	return((!s.empty()) && isalpha(s[0]));
}

Order::Order(std::vector<std::string>& row) {
	if (row.size() < 3) {
		throw std::string("Expected 2 or more fields, found --> ") + to_string(row.size());
	}
	if (isCustomerName(row[0])) {
		customerName = row[0];
	}
	else {
		throw std::string("Expected a customer name, found --> ") + row[0] + " <--";
	}
	if (isProductName(row[1])) {
		productName = row[1];
	}
	else {
		throw std::string("Expected a product name, found --> ") + row[1] + " <--";
	}

	for (int item = 2; item < row.size(); item++) {
		if (isProductName(row[item]))
			order.push_back(row[item]);
	}
}

void Order::print() {
	std::cout << "customer name, product name, [items] = "
		<< customerName << " , "
		<< productName;
	static int number = 1;
	for (auto e : order)
		cout << " , " << e;
	cout << "\n";
	number++;
}

void Order::graph(std::ofstream& of) {
	for(auto e : order)
			of << '"' << e << '"' << "->" << '"' << customerName << "\\n" << productName << '"' << " [color=green];\n";
		of << "\n";
}

OrderManager::OrderManager(std::vector<std::vector<string>> csvData) {
	int rowCount = 0;
	for (auto row : csvData) {
		try {
			rowCount++;
			orderList.push_back(Order(row));
		}
		catch (std::string& e) {
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}

void OrderManager::print() {
	for (auto e : orderList)
		e.print();
}

void OrderManager::graph(std::string& filename) {
	std::ofstream of(filename);
	if (of.is_open()) {
		of << "digraph myGraph {\n";
		for (auto t : orderList)
			t.graph(of);
		of << "}\n";
		of.close();
	}

	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;

	system(cmd.c_str());
}
