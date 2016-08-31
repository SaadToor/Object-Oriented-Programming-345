#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"

class Task {
	std::string name, slot, accept, reject;
	bool isName(std::string& s);
	bool isSlotCount(std::string& s);
public:
	Task(std::vector<std::string>& row);
	std::string& getName();
	std::string& getAccept();
	std::string& getReject();
	void print();
	void graph(std::ofstream& of);
};

class TaskManager {
	std::vector<Task> taskList;
public:
	TaskManager(std::vector<std::vector<std::string>> csvData);
	void print();
	void graph(std::string& filename);
	size_t size();
	std::string& getName(size_t taskIndex);
	std::string& getAccept(size_t taskIndex);
	std::string& getReject(size_t taskIndex);
	Task* find(std::string s);
	Task at(size_t size) const { return taskList[size]; }
	//Task& atT(size_t size) const { return taskList; }
	std::vector<Task> getTasks();
};
