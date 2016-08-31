#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace w5 {
	class Message {
		string name, reply, tweet;
	public:
		Message();
		Message(ifstream& in, char recDelim);
		bool empty() const;
		void display(std::ostream& os) const;

	};//Class Message
}//Namespace of w5