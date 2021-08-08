#ifndef HELP_H_
#define HELP_H_

#include <string>
#include <vector>

struct Client {
	int socket_ID;
	std::string username;
	std::string status;
	std::string work;
};

static std::vector <Client> client_list;

#endif // HELP_H_


