#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include <string>
#include <chrono>
#include <ctime> 
#pragma warning(disable:4996)

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
	//Get the latest gold update by count until the last 3 lines
	std::string information;
	int n = countFileLine("gold.txt");
	std::fstream f("gold.txt", std::fstream::in);
	if (!f) {
		std::cout << "Can't open file!";
		return 0;
	}
	std::string temp;
	for (int i = 0; i < n - 3; i++) {
		std::getline(f, temp, '\n');
	}

	//Get the choice from client
	int choice = 0;
	std::getline(std::cin, temp, '\n');
	if (temp.compare("doji") == 0 || temp.compare("DOJI") == 0) {
		choice = 1;
	}
	else if (temp.compare("sjc") == 0 || temp.compare("SJC") == 0) {
		choice = 2;
	}
	else if (temp.compare("pnj") == 0 || temp.compare("PNJ") == 0) {
		choice = 3;
	}
	
	//Server gives response to client
	Document* d = new Document[3];
	for(int i = 0; i < 3; i++) {
		std::getline(f, information, '\n');
		d[i].Parse(information.c_str());
		for (auto& error : d[i]["results"].GetArray()) {
			for (auto& m : error.GetObject()) {
				if (i + 1 == choice) {
					if (strcmp(m.name.GetString(), "datetime") == 0) {
						std::cout << m.name.GetString() << ": " << m.value.GetString() << std::endl;
					}
					else {
						std::cout << m.name.GetString() << ": " << (double)m.value.GetDouble() << std::endl;
					}
				}
			}
		}
	}

	//Get date & time
	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::string time = std::ctime(&end_time);
	std::cout << "\n" << time;

	f.close();
	return 0;
}