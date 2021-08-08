#ifndef HELP_H_
#define HELP_H_
#include <string>
#include <WinSock2.h>

std::string Receive(SOCKET ClientSocket);
int Convert_char_to_int(char* a, int n);

#endif // !HELP_H_

