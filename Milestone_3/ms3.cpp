#include <string>
#include "factory.h"
#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"

using namespace std;


int validate(ItemManager& im, OrderManager& om, TaskManager& tm) {
	int errors = 0;
	for (size_t ItemIndex = 0; ItemIndex < im.size(); ItemIndex++) {
		string s;
		s = im.getInstaller(ItemIndex);
		if (!tm.find(s)) {
			cerr << "accept task " << s << " missing for task "
				<< im.getName(ItemIndex) << endl;
			errors++;
		}
		s = im.getRevert(ItemIndex);
		if (!tm.find(s)) {
			cerr << "reject task " << s << " missing for item "
				<< im.getName(ItemIndex) << endl;
			errors++;
		}
	}
	for (size_t orderIndex = 0; orderIndex < om.size(); orderIndex++) {
		string s;
		for (size_t itemIndex = 0; itemIndex < om.itemsSize(orderIndex); itemIndex++) {
			s = om.itemListItem(orderIndex, itemIndex);
			if (!im.find(s)) {
				cerr << "installer task " << s << " missing for order "
					<< om.getCustomer(itemIndex) << endl;
				errors++;
			}
		}
	}
	for (size_t taskIndex = 0; taskIndex < tm.size(); taskIndex++) {
		string s;
		s = tm.getAccept(taskIndex);
		if ((!s.empty()) && (!tm.find(s))) {
			cerr << "accept task " << s << " missing for task "
				<< tm.getName(taskIndex) << endl;
			errors++;
		}
		s = tm.getReject(taskIndex);
		if ((!s.empty()) && (!tm.find(s))) {
			cerr << "reject task " << s << " missing for task "
				<< tm.getName(taskIndex) << endl;
			errors++;
		}
	}
	return errors; 
} 

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Usage : " << argv[0] << "item-csv order-csv task-csv csv-seperator\n";
		return 1;
	}
	string itemFile = argv[1];
	string orderFile = argv[2];
	string taskFile = argv[3];
	char   seperator = argv[4][0];

	try {
		string f;
		vector<vector<string>> itemCsvData;
		vector<vector<string>> orderCsvData;
		vector<vector<string>> taskCsvData;

		csvReader(itemFile, seperator, itemCsvData);
		csvReader(orderFile, seperator, orderCsvData);
		csvReader(taskFile, seperator, taskCsvData);

		ItemManager im(itemCsvData);
		im.print();
		f = itemFile + string(".gv");
		im.graph(f);

		OrderManager om(orderCsvData);
		om.print();
		f = orderFile + string(".gv");
		om.graph(f);

		TaskManager tm(taskCsvData);
		tm.print();
		f = taskFile + string(".gv");
		tm.graph(f);
		int error = validate(im, om, tm);
		if (error) {
			throw std::to_string(error) + string(" errors in data files.  Fix errors and re-run.");
		}
		Factory fc(im, om, tm);
	}
	catch (string& e) {
		cerr << e << "\n";
	}
	return 0;
}
