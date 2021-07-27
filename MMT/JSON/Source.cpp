#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include <string>

using namespace rapidjson;

int countFileLine(std::string filename) {
	std::fstream f(filename, std::fstream::in);
	int n = 0;
	std::string temp;
	while (!f.eof()) {
		std::getline(f, temp, '\n');
		n += 1;
	}
	f.close();
	return n;
}

int main() {
	std::string information;
	int n = countFileLine("gold.txt");

	std::fstream f("gold.txt", std::fstream::in);
	if (!f) {
		std::cout << "Can't open file!";
		return 0;
	}
	
	std::string temp;
	for (int i = 0; i < 3; i++) {
		std::getline(f, temp, '\n');
	}

	std::getline(std::cin, temp, '\n');

	Document* d = new Document[3];
	for(int i = 0; i < 3; i++) {
		std::getline(f, information, '\n');
		d[i].Parse(information.c_str());
		for (auto& error : d[i]["results"].GetArray()) {
			for (auto& m : error.GetObject()) {
				/*if (strcmp(m.name.GetString(), "datetime") == 0) {
					std::cout << m.name.GetString() << ": " << m.value.GetString() << std::endl;
				}
				else {
					std::cout << m.name.GetString() << ": " << (double)m.value.GetDouble() << std::endl;
				}*/
				if (strcmp(m.name.GetString(), temp.c_str()) == 0) {
					std::cout << m.name.GetString() << ": " << (double)m.value.GetDouble() << std::endl;
				}
			}
		}
		std::cout << "\n";
	}

	f.close();
	return 0;
}