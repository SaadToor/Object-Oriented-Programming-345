#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
#include "Job.h"
#include "machine.h"

using namespace std;

class Factory {
private:
	ItemManager im;
	OrderManager om;
	TaskManager tm;
	vector<Job> jb;
	vector<Machine> mc;
public:
	Factory(ItemManager& ims, OrderManager& oms, TaskManager& tms);
};

