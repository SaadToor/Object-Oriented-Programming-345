#pragma once
#include <cctype>
#include <queue>
#include "i.h"
#include "o.h"
#include "t.h"
#include "Job.h"

using namespace std;

class Machine : public Task {
	bool            bInstaller;
	bool			bRemover;
	bool			bSink;
	std::queue<Job> inputQ;
	Job				job;
public:
	Machine(Task tt, ItemManager im);
	void push(Job&& j) { return inputQ.push( move(j) ); }
	bool isEmpty() { return inputQ.empty(); }
	void print(std::ostream& os);
	void classify(ItemManager& im);
	void run(ItemManager& i, vector<Machine>& mc);
};
