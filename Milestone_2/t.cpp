// Exaxt same as Task.cpp

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
#include "t.h"
using namespace std;

bool Task :: isName(std::string& s){
	return ((! s.empty()) && isalpha(s[0]));
}

bool Task :: isSlotCount(std::string& s){
	if(s.empty())
		return false;
	for(auto c : s)
		if(! isdigit(c))
			return false;
	return true;
}

Task :: Task(std::vector<std::string>& row):slot("1"){
	switch (row.size()){
		case 4:
			if(isName(row[3]))
				reject = row[3];
			else
				throw std::string("Expected a reject task, found --> ") + row[3] + " <--";
		case 3:
			if(isName(row[2]))
				accept = row[2];
			else
				throw std::string("Expected a accept task, found --> ") + row[2] + " <--";
		case 2:
			if(isSlotCount(row[1]))
				slot = row[1];
			else
				throw std::string("Expected a slot task, found --> ") + row[1] + " <--";
		case 1:
			if(isName(row[0]))
				name = row[0];
			else
				throw std::string("Expected a task, found --> ") + row[0] + " <--";
		default:
			if(row.size() < 1)
				throw std::string("Ecxpected 1,2,3, or 4 feilds, found ") + std::to_string(row.size());
	}
}

std::string& Task::getName(){
	return name;
}

std::string& Task::getAccept(){
	return accept;
}

std::string& Task::getReject(){
	return reject;
}

void Task :: print(){
	std::cout << "name, slots, accept, reject = "
	<< name << " / " << slot << " / " << accept << " / " << reject << " / \n";
}

void Task :: graph(std::ofstream& of){
	if(! accept.empty())
			of << '"' << "TASK\\n" << name << '"' << "->" << '"' << "TASK\\n" << accept << '"' << " [color=green];\n";
	if(! reject.empty())
		of << '"' << "TASK\\n" << name << '"' << "->" << '"' << "TASK\\n" << reject << '"' << " [color=red];\n";
	
	if(accept.empty() && reject.empty())
		of << '"' << "TASK\\n" << name << '"' << std::endl;
}


TaskManager :: TaskManager(std::vector<std::vector<std::string>> csvData){
	int rowCount=0;
	for(auto row : csvData){
		try{
			rowCount++;
			taskList.push_back(Task(row));
		}catch(std::string& e){
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}

void TaskManager :: print(){
	for(auto t : taskList)
		t.print();
}

void TaskManager :: graph(std::string& filename){
	std::ofstream of(filename);
	if(of.is_open()){
		of << "digraph myGraph {\n";
		for(auto t : taskList)
			t.graph(of);
		of << "}\n";
		of.close();
	}
	
	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;
	
	system(cmd.c_str());
}

size_t TaskManager :: size(){
	return taskList.size();
}

string& TaskManager :: getAccept(size_t taskIndex){
	return taskList[taskIndex].getAccept();
}

string& TaskManager :: getReject(size_t taskIndex){
	return taskList[taskIndex].getReject();
}

string& TaskManager :: getName(size_t taskIndex){
	return taskList[taskIndex].getName();
}

Task* TaskManager :: find(std::string name){
	for(size_t t = 0; t < taskList.size(); t++){
		if(name == taskList[t].getName())
			return &taskList[t];
	}
	return nullptr;
}
