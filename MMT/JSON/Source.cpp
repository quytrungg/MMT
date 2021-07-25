#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include <string>

using namespace rapidjson;

int main() {
	std::string information;
	std::fstream f("gold.txt", std::fstream::in);
	if (!f) {
		std::cout << "Can't open file!";
		return 0;
	}
	Document* d = new Document[3];
	for(int i = 0; i < 3; i++) {
		std::getline(f, information, '\n');
		d[i].Parse(information.c_str());
		for (auto& error : d[i]["results"].GetArray()) {
			for (auto& m : error.GetObject()) {
				if (strcmp(m.name.GetString(), "datetime") == 0) {
					std::cout << m.name.GetString() << ": " << m.value.GetString() << std::endl;
				}
				else {
					std::cout << m.name.GetString() << ": " << (double)m.value.GetDouble() << std::endl;
				}
			}
		}
		std::cout << "\n";
	}

	f.close();
	return 0;
}