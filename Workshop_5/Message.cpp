#include "Message.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace w5 {
		Message::Message() {}
		Message::Message(ifstream& in, char recDelim) {
			string line;
			getline(in, line, recDelim);
			int index = 0;
			while (index < line.size() && line[index] != ' ')
				name += line[index], index++;

			if (line[index] == ' ')
				index++;

			if (index < line.size() && line[index] == '@') {
				index++;
				while (index < line.size() && line[index] != ' ')
					reply += line[index], index++;
				index++;
			}
			while (index < line.size())
				tweet += line[index++];
		}
		bool Message::empty() const {
			return tweet.empty();
		}
		void Message::display(std::ostream& os) const {
			os << "Messsage\n"
				<< "User  : " << name << endl;
			if (!reply.empty()) {
				os << "Reply : " << reply << endl;
			}
			if (!empty()) {
				os << "Tweet : " << tweet << endl;
			}
			os << endl;
		}
}//Namespace of w5