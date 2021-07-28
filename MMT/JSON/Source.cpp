#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include <string>
#include <ctime> 
#include <sstream>
#pragma warning(disable:4996)

using namespace rapidjson;

int countFileLine(std::string filename) {
	std::fstream f(filename, std::fstream::in);
	if (!f) {
		return -1;
	}
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
	//Choose date
	std::string temp, information;
	do {
		std::cout << "Choose your date (yyyy-mm-dd): ";
		std::getline(std::cin, temp, '\n');

		//Get the latest gold update by count until the last 3 lines
		int n = countFileLine(temp + ".json");
		std::fstream f(temp + ".json", std::fstream::in);
		if (!f) {
			if (temp.compare("exit") == 0) return 0;
			std::cout << "Can't open file!\n";
			continue;
		}
		for (int i = 0; i < n - 3; i++) {
			std::getline(f, temp, '\n');
		}

		//Choose gold type
		int choice = 0;
		std::cout << "Choose your gold type (DOJI, SJC, PNJ): ";
		std::getline(std::cin, temp, '\n');
		std::cout << "\n";
		if (temp.compare("doji") == 0 || temp.compare("DOJI") == 0) {
			choice = 1;
		}
		else if (temp.compare("sjc") == 0 || temp.compare("SJC") == 0) {
			choice = 2;
		}
		else if (temp.compare("pnj") == 0 || temp.compare("PNJ") == 0) {
			choice = 3;
		}
		else {
			std::cout << "Can't find gold type!\n";
			continue;
		}

		//Server gives response to client
		Document* d = new Document[3];
		for (int i = 0; i < 3; i++) {
			std::getline(f, information, '\n');
			if (information == "") break;
			d[i].Parse(information.c_str());
			for (auto& error : d[i]["results"].GetArray()) {
				for (auto& m : error.GetObject()) {
					if (i + 1 == choice) {
						if (strcmp(m.name.GetString(), "datetime") == 0) {
							d[i].RemoveMember("datetime");
							//std::cout << m.name.GetString() << ": " << m.value.GetString() << std::endl;
						}
						else {
							std::cout << m.name.GetString() << ": " << (double)m.value.GetDouble() << std::endl;
						}
					}
				}
			}
		}
		std::cout << "\n";
		delete[] d;
		f.close();
	} while (temp.compare("exit") != 0);
	return 0;
}