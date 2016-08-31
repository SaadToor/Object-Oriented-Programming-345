#include "machine.h"

Machine::Machine(Task tt, ItemManager im)
:Task(tt),bInstaller(false),bRemover(false),bSink(false){
	classify(im);
}

void Machine::print(std::ostream & os){
	os << "Machine name is " << getName();
	if (bInstaller)						os << " <-- installer";
	if (bRemover)						os << " <-- remover";
	if (bSink)							os << " <-- sync!";
	if ((!bInstaller)&&(!bRemover))		os << " <-- neither installer no remover";
	os << "\n";
}

void Machine::classify(ItemManager& im){
	for (size_t it = 0; it != sizeof(im); it++) {
		if (getName() == im.getInstaller(it))	bInstaller = true;
		if (getName() == im.getRevert(it))	bRemover   = true;
	}
	if (bInstaller && bRemover)
		throw getName() + " is both an installer and a remover. Fix item data resume";
}

void Machine::run(ItemManager & i, vector<Machine>& mc){
	if (inputQ.empty())
		return;

	job = move(inputQ.front());
	inputQ.pop();

	cout << "Job = ";
	job.print();

	if (bSink) {
		if (job.isComplete()) {
			cout << "' " << job.getProductName() << " '"
				 << " completed for customer ' " << job.getCustomerName() << " '"
				 << "\n";
		}
		else {
			throw string("job at sync node ") + getName() + " but job is not comlpete";
		}
	}

	auto route = [&mc,this](Job& job, string destination) {
		for (auto m = mc.begin(); m < mc.end(); m++) {
			if (m->getName() == destination) {
				m->push(move(job));
				cout << "route moving job from ' " << this->getName() << " ' to ' " << destination << "\n";
				break;
			}
		}
	};

	bool didSomething = false;
	if (bInstaller) {
		for (size_t item = 0; item < job.getItemList().size(); item++) {
			if (job.isInstalled(item))
				continue;
			string itemName;
			for (size_t t = 0; t < job.getItemList().size(); t++) {
				if (!job.isInstalled(t)) {
					itemName = job.getItem(t);
				}
			}
			Item* itemPtr = i.find(itemName);
			if (itemPtr && itemPtr->getInstaller() == getName()) {
				job.Install(item);
				didSomething = true;
			}
			else {
				cout << "item " << itemName << " needs installer "
					<< itemPtr->getInstaller() << ", (not us)\n";
			}
		}
	}

	if (bRemover) {
		for (size_t item = 0; item < job.getItemList().size(); item++) {
			if (!job.isInstalled(item))
				continue;
			string itemName;
			for (size_t t = 0; t < job.getItemList().size(); t++) {
				if (!job.isInstalled(t)) {
					itemName = job.getItem(t);
				}
			}
			Item* itemPtr = i.find(itemName);
			if (itemPtr && itemPtr->getRevert() == getName()) {
				job.Remover(item);
				didSomething = true;
			}
			else {
				cout << "item " << itemName << " need remover " << itemPtr->getRevert() << ", (not us)\n";
			}
		}
	}

	string passed = getAccept();
	
	if (!didSomething) {
		route(job,passed);
		return;
	}

	string failed = getReject();

	if (failed.empty()) {
		route(job,passed);
		return;
	}

	if (rand()%2) {
		cout << "Machine " << getName() << " COIN FLIP job **PASSED!** \n";
		route(job,passed);
		return;
	}
	else {
		cout << "Machine " << getName() << " COIN FLIP job **FAILED!** \n";
		route(job, passed);
		return;
	}
}
