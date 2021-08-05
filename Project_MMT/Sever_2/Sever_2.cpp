#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

struct Account {
    std::string username;
    std::string password;
    int online;
};

std::vector <Account> account;

SOCKET ConectClient() {
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    return ListenSocket;
}

bool checkFileWithFstream_string(std::string path) {
    std::ifstream isf(path);
    return isf.good();
}

std::vector <Account> Read_File_Account(std::string file_name) {
    std::vector <Account> account;
    std::ifstream fin(file_name);
    std::string str;
    if (!fin) {

    }
    else {
        while (!fin.eof()) {
            Account Add;
            std::getline(fin, str);
            if (str != "") {
                std::stringstream ss(str);
                std::getline(ss, Add.username, ',');
                ss >> Add.password;
            }
            account.push_back(Add);
        }
    }
    fin.close();
    return account;
}

void Write_File_Account(std::vector <Account> account, std::string file_name) {
    std::ofstream fout(file_name);
    for (int i = 0; i < account.size(); i++) {
        if (account[i].username != "" && account[i].password != "") {
            fout << account[i].username << "," << account[i].password << std::endl;
        }
    }
    fout.close();
}

bool Check_Username(std::vector <Account> account, std::string username) {
    for (int i = 0; i < account.size(); i++) {
        if (account[i].username.compare(username) == 0) return true;
    }
    return false;
}

bool Check_Account(std::vector <Account> account, std::string username, std::string password) {
    for (int i = 0; i < account.size(); i++) {
        if (account[i].username.compare(username) == 0) {
            if (account[i].password.compare(password) == 0) {
                return true;
            }
            else return false;
        }
    }
    return false;
}

void Sign_up(SOCKET ClientSocket) {
    Account Add;
    int iResult;
    char username[1024];
    char password[1024];
    int check = 1;
    do {
        check = 1;
        memset(username, 0, sizeof(username));
        iResult = recv(ClientSocket, username, sizeof(username), 0);
        memset(password, 0, sizeof(password));
        iResult = recv(ClientSocket, password, sizeof(password), 0);
        std::string str_1(username);
        std::string str_2(password);
        Add.username = str_1;
        Add.password = str_2;
        if (Check_Username(account, Add.username)) {
            check = 0;
            iResult = send(ClientSocket, "0", 2, 0);
        }
        else {
            iResult = send(ClientSocket, "1", 2, 0);
        }
    } while (check != 1);
    account.push_back(Add);
}

void Log_in(SOCKET ClientSocket) {
    int iResult;
    char username[1024];
    char password[1024];
    int check = 1;
    do {
        check = 1;
        memset(username, 0, sizeof(username));
        iResult = recv(ClientSocket, username, sizeof(username), 0);
        memset(password, 0, sizeof(password));
        iResult = recv(ClientSocket, password, sizeof(password), 0);
        std::string Check_username(username);
        std::string Check_password(password);
        if (Check_Account(account, username, password)) {
            iResult = send(ClientSocket, "1", 2, 0);
        }
        else {
            check = 0;
            iResult = send(ClientSocket, "0", 2, 0);
        }
    } while (check != 1);
    std::cout << username << std::endl;
}

void Client_Connect(SOCKET ClientSocket) {
    int iResult;
    char respond[DEFAULT_BUFLEN];
    while (1) {
        iResult = recv(ClientSocket, respond, DEFAULT_BUFLEN, 0);
        if (strcmp(respond, "signup") == 0) {
            Sign_up(ClientSocket);
        }
        else if (strcmp(respond, "signin") == 0) {
            Log_in(ClientSocket);
        }
        break;
    }
}

void Process(SOCKET ListenSocket) {
    account = Read_File_Account("account.txt");
    SOCKET ClientSocket;
    int count = 0;
    while (count != 5) {
        ClientSocket = accept(ListenSocket, NULL, NULL);
        std::thread connect(Client_Connect, ClientSocket);
        connect.detach();
        count++;
    }
    Write_File_Account(account, "account.txt");
}

int Send(SOCKET ClientSocket, char a[]) {
    char b[1024];
    memset(b, 0, sizeof(b));
    int k = 0;
    for (int i = 0; i <= sizeof(a); i++) {
        b[i] = a[i];
        k++;
    }
    b[k] = '\\';
    b[k + 1] = 'w';
    b[k + 2] = '\0';
    return send(ClientSocket, b, sizeof(b), 0);
}

std::string Receive(SOCKET ClientSocket) {
    int receive = 0;
    std::string b = "";
    char a[1024];
    do {
        memset(a, 0, 1024);
        receive = recv(ClientSocket, 0, 1024, 0);
        if (strstr(a, "\w") != nullptr) {
            char* c = strstr(a, "\w");
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
}

int main() {
    SOCKET ListenSocket = ConectClient();
    Process(ListenSocket);
    closesocket(ListenSocket);
    WSACleanup();
}