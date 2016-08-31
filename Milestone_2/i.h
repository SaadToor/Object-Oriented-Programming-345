// Exaxt same as Item.cpp

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"

class Item{
	std::string name, installer, code, remover, description;
	bool isItemName(std::string& s);
	bool isCode(std::string& s);
	public:
	Item(std::vector<std::string>& row);
	void print();
	void graph(std::ofstream& of);
	std::string& getName();
	std::string& getInstaller();
	std::string& getRevert();
};

class ItemManager{
	std::vector<Item> ItemList;
	public:
	ItemManager(std::vector<std::vector<std::string>> csvData);
	void print();
	void graph(std::string& filename);
	size_t size();
	Item* find(std::string s);
	std::string& getName(size_t itemIndex);
	std::string& getInstaller(size_t itemIndex);
	std::string& getRevert(size_t itemIndex);
};
