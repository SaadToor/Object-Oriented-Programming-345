#pragma once
#include "o.h"

class Job : public Order {
	std::vector<bool> vBools; //True if o.getItemsOrdered[i] is installed
public:
	Job() {}
	Job(Order ord);
	bool isComplete();
	void Install(int check) { vBools[check] = true; }
	void Remover(int check) { vBools[check] = false; }
	bool isInstalled(int check) { return vBools[check]; }
};
