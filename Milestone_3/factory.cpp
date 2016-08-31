#include "factory.h"

Factory::Factory(ItemManager& ims, OrderManager& oms, TaskManager& tms) :im(move(ims)), om(move(oms)), tm(move(tms)) {
	// Load the Machines, one per task
	for (size_t m = 0; m < tm.size(); m++)
		mc.push_back(Machine(tm.at(m), im));
	std::vector<Task> tasks = tm.getTasks();
	// Find the source machine
	enum { SOURCE_NOT_FOUND = -1 };
	int sourceMachine = SOURCE_NOT_FOUND;
	
	for (size_t m = 0; m < tasks.size(); m++) {
		if (sourceMachine == SOURCE_NOT_FOUND) {
			if (!tasks[m].getAccept().empty() && tasks[m].getReject().empty()) {
				size_t j = 0;
				for (; j < tasks.size(); j++) {
					if (tasks[m].getName() == tasks[j].getAccept() || tasks[m].getName() == tasks[j].getReject())
						break;
				}
				if (j == tasks.size()) {
					cout << tasks.at(m).getName() << " is a source\n";
					sourceMachine = m;
					std::cout << tasks[m].getName() << std::endl;
				}
			}
		}
		else
			throw string("cannot build factory: multiple sources nodes, fix data and resubmit");
	}
	
	// Load jobs into tsource machine, one job per order
	for (size_t j = 0; j < om.size(); j++)
		mc.at(sourceMachine).push(move(Job(om.at(j))));

	// Time loop
	for (int time = 0;  ; time++) {
		cout << "\n\nTIME LOOP TOP, time= " << time << "\n";
		bool finished = true;
		for (size_t m = 0; m < mc.size(); m++) {
			if (!mc[m].isEmpty()) {
				finished = false;
				cout << "Machine scan: " << mc[m].getName() << " has job\n";
			}
		}
		if (finished) {
			cout << "----------------------------------\n"
				 << "- No jobs waiting for processing -\n"
				 << "- Factory simulation complete    -\n"
				 << "----------------------------------\n";
			break;
		}
		
		// Machine Loop
		for (size_t m = 0; m < mc.size(); m++)
			mc[m].run(im, mc);
	}
}
