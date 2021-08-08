#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Help.h"

std::string Receive(SOCKET ClientSocket) {
    int receive = 0;
    std::string b = "";
    char a[1024];
    do {
        memset(a, 0, 1024);
        receive = recv(ClientSocket, a, 1024, 0);
        if (strstr(a, "\v") != nullptr) {
            char* c = strstr(a, "\v");
            char temp[1024] = "";
            int count = c - a;
            for (int i = 0; i < count; i++) {
                temp[i] = a[i];
            }
            b += temp;
            break;
        }
        b += a;
    } while (receive > 0);
    return b;
}

int Convert_char_to_int(char* a, int n)
{
    int m = 0;
    int p;
    for (int i = 0; i < n; i++) {
        p = a[i] - L'0';
        m = m * 10 + p;
    }
    return m;
}