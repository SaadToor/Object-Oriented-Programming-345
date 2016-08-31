#include "Notifications.h"
#include <fstream>
#include <iostream>
#include "Message.h"

using namespace std;

namespace w5 {
		Notifications::Notifications()
			:msgTable(nullptr), count(0) {
			msgTable = new Message[CAPACITY];
		}
		void Notifications::operator+=(const Message& msg) {
			if (count < CAPACITY) {
				msgTable[count++] = msg;
			}
		}

		Notifications::Notifications(const Notifications& rhs) :msgTable(new Message[CAPACITY]), count(rhs.count) {
			for (int i = 0; i < count; i++) {
				msgTable[i] = rhs.msgTable[i];
			}
		}
		Notifications& Notifications::operator=(const Notifications& rhs) {
			if (this != &rhs) {
				if (!msgTable) {
					msgTable = new Message[CAPACITY];
					count = rhs.count;
					for (int i = 0; i < count; i++) {
						msgTable[i] = rhs.msgTable[i];
					}
				}
			}
			return *this;
		}
		Notifications::Notifications(Notifications&& rhs)
			:msgTable(rhs.msgTable), count(rhs.count) {
			rhs.msgTable = nullptr;
			rhs.count = 0;
		}
		Notifications&& Notifications::operator=(Notifications&& rhs) {
			if (this != &rhs) {
				count = rhs.count;
				if (msgTable) {
					delete[] msgTable;
					msgTable = rhs.msgTable;
					count = rhs.count;

					rhs.count = 0;
					rhs.msgTable = nullptr;
				}
			}
			return move(*this);
		}
		Notifications::~Notifications() {
			delete[] msgTable;
		}
		void Notifications::display(std::ostream& os) {
			for (int i = 0; i < count; i++) {
				msgTable[i].display(os);
			}
		}
}//Namespace of w5