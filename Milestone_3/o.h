#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
using namespace std;
class Order {
	std::string customerName, productName;
	std::vector<std::string> order;
	bool isCustomerName(std::string& s);
	bool isProductName(std::string& s);
public:
	Order() {}
	Order(std::vector<std::string>& row);
	void print();
	void graph(std::ofstream& of);
	size_t size() { return order.size(); }
	std::string& getItem(size_t itemIndex) { return order[itemIndex]; }
	std::string& getCustomerName() { return customerName; }
	std::string& getProductName() { return productName; }
	std::vector<std::string> getItemList() { return order; }
};

class OrderManager {
	std::vector<Order> orderList;
public:
	OrderManager(std::vector<std::vector<string>> csvData);
	void print();
	void graph(std::string& filename);
	size_t size() { return orderList.size(); }
	size_t itemsSize(size_t orderIndex) { return orderList[orderIndex].size(); }
	std::string& itemListItem(size_t orderIndex, size_t itemIndex) { return orderList[orderIndex].getItem(itemIndex); }
	std::string& getCustomer(size_t orderIndex) { return orderList[orderIndex].getCustomerName(); }
	Order at(size_t s) { return orderList[s]; }
};
