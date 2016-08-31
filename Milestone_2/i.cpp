//// Exaxt same as Item.cpp

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
#include "i.h"
#include "o.h"

bool Item::isItemName(std::string& s){
	return ((!s.empty()) && isalpha(s[0]));
}

bool Item::isCode(std::string & s){
	if (s.empty())
		return false;
	for (auto c : s)
		if (!isdigit(c))
			return false;
	return true;
}

Item ::Item(std::vector<std::string>& row):code("1"){
	switch (row.size()){
		case 5:
			description = row[4];
		case 4:
			if(isCode(row[3]))
				code = row[3];
			else
				throw std::string("Expected a code, found --> ") + row[3] + " <--";
		case 3:
			if(isItemName(row[2]))
				remover = row[2];
			else
				throw std::string("Expected a remover task name, found --> ") + row[2] + " <--";
		case 2:
			if(isItemName(row[1]))
				installer = row[1];
			else
				throw std::string("Expected a installer task slot, found --> ") + row[1] + " <--";
		case 1:
			if(isItemName(row[0]))
				name = row[0];
			else
				throw std::string("Expected a item name, found --> ") + row[0] + " <--";
		default:
			if(row.size() < 4)
				throw std::string("Ecxpected 4 or 5 feilds, found ") + std::to_string(row.size());
	}
}

void Item :: print(){
	std::cout << "name, slots, accept, reject = "
	<< name << " , " 
	<< installer << " , " 
	<< remover << " , " 
	<< code << " , ";
	if(! description.empty())
	std::cout << description << "\n";
	std::cout << "\n";
}

void Item :: graph(std::ofstream& of){
	of << '"' << "ITEM\\n" << name << '"' << "->" << '"' << " INSTALLER\\n" << installer << '"' << " [color=green];\n";
	of << '"' << "ITEM\\n" << name << '"' << "->" << '"' << " REMOVER\\n" << remover << '"' << " [color=red];\n";
}

std::string& Item::getName(){
	return name;
}

std::string& Item::getInstaller(){
	return installer;
}

std::string& Item::getRevert(){
	return remover;
}



ItemManager :: ItemManager(std::vector<std::vector<std::string>> csvData){
	int rowCount=0;
	for(auto row : csvData){
		try{
			rowCount++;
			ItemList.push_back(Item(row));
		}catch(std::string& e){
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}

void ItemManager :: print(){
	for(auto e : ItemList)
		e.print();
}

void ItemManager :: graph(std::string& filename){
	std::ofstream of(filename);
	if(of.is_open()){
		of << "digraph myGraph {\n";
		for(auto t : ItemList)
			t.graph(of);
		of << "}\n";
		of.close();
	}	
	//Ask Sir for help?
	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;
	
	system(cmd.c_str());
	std::cout << std::endl;
}

size_t ItemManager::size(){
	return ItemList.size();
}

Item* ItemManager::find(std::string name){
	for (size_t i = 0; i < ItemList.size(); i++) {
		if (name == ItemList[i].getName())
			return &ItemList[i];
	}
}

std::string & ItemManager::getName(size_t itemIndex){
	return ItemList[itemIndex].getName();
}

std::string & ItemManager::getInstaller(size_t itemIndex){
	return ItemList[itemIndex].getInstaller();
}

std::string & ItemManager::getRevert(size_t itemIndex){
	return ItemList[itemIndex].getRevert();
}
