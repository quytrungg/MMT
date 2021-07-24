#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include <string>

using namespace rapidjson;

void addSlash(std::string line) {
	for (int i = 0; i < line.length(); i++) {
		
	}
}

int main() {
	std::string information;
	std::fstream f("test.txt", std::fstream::in);
	std::getline(f, information);

	char* json = new char[information.length() + 1];
	for (int i = 0; i < information.length(); i++) {
		json[i] = information[i];
	}

	const char* test = "{\"results\":[{\"buy_ct\":56800000.0,\"buy_dn\":56800000.0,\"buy_hcm\":56750000.0,\"buy_hn\":56800000.0,\"datetime\":1627008008,\"sell_ct\":57500000.0,\"sell_dn\":57550000.0,\"sell_hcm\":57500000.0,\"sell_hn\":57550000.0}]}";

	Document d;
	d.Parse(test);

	for (auto& error : d["results"].GetArray())
		for (auto& m : error.GetObject())
			std::cout << m.name.GetString() << ": " << m.value.GetDouble() << std::endl;

	/*const Value& array = d["results"];

	for (SizeType i = 0; i < array.Size(); i++)
	{
		std::cout << array[i].GetDouble() << " ";
	}*/

	f.close();

	return 0;
}