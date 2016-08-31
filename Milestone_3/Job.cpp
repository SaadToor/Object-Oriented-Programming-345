#include "Job.h"

using namespace std;

Job::Job(Order ord):Order(ord){
	for (size_t i = 0; i < ord .size(); i++) {
		vBools.push_back(false);
	}
}

bool Job::isComplete(){
	for (auto e : vBools)	// Look for something not installed
		if (!e)				// not complete
			return false;
	return true;			// yes complete
}

