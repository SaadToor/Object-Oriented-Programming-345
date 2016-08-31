#pragma once
#include <fstream>
#include <iostream>
#include "Message.h"

#define CAPACITY 10

using namespace std;

namespace w5 {
	class Notifications {
		Message* msgTable;
		int count;
	public:
		Notifications();
		void operator+=(const Message& msg);

		Notifications(const Notifications& rhs);
		Notifications& operator=(const Notifications& rhs);
		Notifications(Notifications&& rhs);
		Notifications&& operator=(Notifications&& rhs);
		~Notifications();
		void display(std::ostream& os);
	};
}//Namespace of w5