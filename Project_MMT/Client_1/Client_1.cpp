#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#define Address "192.168.0.104"

#pragma comment (lib, "Ws2_32.lib")

struct Account {
    std::string username;
    std::string password;
    Account* next;
};

std::string InputHidden() {
    char temp;
    std::string pass;
    while (true)
    {
        temp = _getwch();
        if (temp == 13) break;
        else if (temp == 27) return "";
        if (temp == 8) {
            if (pass.size() != 0) {
                pass.pop_back();
                std::cout << temp << ' ' << temp;
            }
        }
        if (temp >= ' ' && temp <= '~') {
            std::cout << "*";
            pass.push_back(temp);
        }
    }
    std::cout << '\n';
    return pass;
}

SOCKET Conect_to_sever() {
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    const char* sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(Address, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    return ConnectSocket;
}

bool Sign_in(SOCKET ConnectSocket) {
    int iResult;
    iResult = send(ConnectSocket, "0", 2, 0);
    Account Add;
    int check = 1;
    char respond[DEFAULT_BUFLEN];
    char a[] = "0";
    char b[] = "1";
    do {
        check = 1;
        system("cls");
        std::cout << "Username: ";
        std::getline(std::cin, Add.username);
        char* username = new char[Add.username.length() + 1];
        Add.username.copy(username, Add.username.length(), 0);
        username[Add.username.length()] = '\0';
        iResult = send(ConnectSocket, username, (int)strlen(username), 0);
        iResult = recv(ConnectSocket, respond, DEFAULT_BUFLEN, 0);
        if (strcmp(respond, a) == 0) {
            check = 0;
            std::cout << "Username is already in use" << std::endl;
            Sleep(500);
        }
    } while (check == 0);
    std::cout << "Password: ";
    Add.password = InputHidden();
    char* password = new char[Add.password.length() + 1];
    Add.password.copy(password, Add.password.length(), 0);
    password[Add.password.length()] = '\0';
    iResult = send(ConnectSocket, password, (int)strlen(password), 0);
    iResult = recv(ConnectSocket, respond, DEFAULT_BUFLEN, 0);
    if (strcmp(respond, b) == 0) {
        std::cout << "Sign in success" << std::endl;
        return true;
    }
    else {
        std::cout << "Sign in not success" << std::endl;
        return false;
    }
}

void Log_in(SOCKET ConnectSocket) {
    int iResult;
    iResult = send(ConnectSocket, "1", 2, 0);
    Account Check;
    int check = 0;
    char respond[DEFAULT_BUFLEN];
    char a[] = "0";
    char b[] = "1";
    do {
        do {
            check = 1;
            system("cls");
            std::cout << "Username: ";
            std::getline(std::cin, Check.username);
            char* username = new char[Check.username.length() + 1];
            Check.username.copy(username, Check.username.length(), 0);
            username[Check.username.length()] = '\0';
            iResult = send(ConnectSocket, username, (int)strlen(username), 0);
            iResult = recv(ConnectSocket, respond, DEFAULT_BUFLEN, 0);
            if (strcmp(respond, a) == 0) {
                check = 0;
                std::cout << "Username incorect" << std::endl;
                Sleep(500);
            }
        } while (check == 0);
        std::cout << "Password: ";
        Check.password = InputHidden();
        char* password = new char[Check.password.length() + 1];
        Check.password.copy(password, Check.password.length(), 0);
        password[Check.password.length()] = '\0';
        iResult = send(ConnectSocket, password, (int)strlen(password), 0);
        iResult = recv(ConnectSocket, respond, DEFAULT_BUFLEN, 0);
        if (strcmp(respond, b) == 0) {
            check = 1;
            std::cout << "Log in success" << std::endl;
        }
        else {
            check = 0;
            std::cout << "Password incorect" << std::endl;
            Sleep(500);
        }
    } while (check == 0);
}

int main() {
    SOCKET ConnectSocket = Conect_to_sever();

    std::cout << "1. Sign in" << std::endl;
    std::cout << "2. Log in" << std::endl;
    int n;
    std::cin >> n;
    std::cin.ignore();
    switch (n)
    {
    case 1:
        Sign_in(ConnectSocket);
        break;
    case 2:
        Log_in(ConnectSocket);
        break;
    }

    //Sleep(10000);
    //cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}