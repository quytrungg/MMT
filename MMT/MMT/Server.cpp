#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <WinSock2.h>
#include <string>
#include <WS2tcpip.h>
#include <thread>
#include <sstream>
#include <winhttp.h>
#include <fstream>
#include <sql.h>
#include <windows.data.json.h>
#include <ctime>
#include <sstream>

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "2000"
#pragma warning(disable:4996)

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "winhttp.lib")

//Overall variable
std::wstring API_KEY = L"";

//Struct
struct Account {
    std::string username;
    std::string password;
    int sock_cli;
    std::thread process;
    bool check;
    Account* next;
};

//Send message to user if connect successfully
void accountConnect(Account* acc) {
    std::string noti = "ACCEPTED!\n";
    std::cout << acc->username << " is login!\n";
    send(acc->sock_cli, noti.c_str(), noti.size(), 0);
}

bool updateStatus = false;
Account* activeAccount = nullptr;

//Activate an account
void activateAccount(std::string username, std::string password, int sock_cli) {
    activeAccount = new Account{ username, password, sock_cli, std::thread(), true, activeAccount };
    activeAccount->process = std::thread(accountConnect, activeAccount);
    activeAccount->process.detach();
}

//Deactivate an account
void deactivateAccount(std::string username) {
    Account* temp = new Account;
    temp->next = activeAccount;
    while (temp->next != nullptr && temp->next->username.compare(username) != 0) {
        temp = temp->next;
    }
    if (temp->next != nullptr) {
        Account* del = temp->next;
        temp->next = temp->next->next;
        del->process.~thread();
        send(del->sock_cli, "LOGOUT\n", 6, 0);
        delete del;
    }
    temp = activeAccount;
    activeAccount = temp->next;
    delete temp;
    return;
}

//Take the API from third party
std::wstring takeAPI(HINTERNET connectToServer) {
    std::wstring noti = L"/api/request_api_key?scope=gold";
    std::string temp = "";
    HINTERNET hiRequest = WinHttpOpenRequest(connectToServer, L"GET", noti.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    bool hiResult = WinHttpSendRequest(hiRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    bool hiResponse = WinHttpReceiveResponse(hiRequest, NULL);
    DWORD dwSize = 0, dwPull = 0;
    char* dwBuffer;
    if (hiResponse) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hiRequest, &dwSize)) {
                std::cout << "Error " << GetLastError() << " query data unavailable!\n";
            }
            dwBuffer = new char[dwSize + 1];
            if (!dwBuffer) {
                std::cout << "Out of memory!\n";
                dwSize = 0;
            }
            else{
                ZeroMemory(dwBuffer, dwSize + 1);
                if (!WinHttpReadData(hiRequest, (LPVOID)dwBuffer, dwSize, &dwPull)) {
                    std::cout << "Error " << GetLastError() << " winhttp can't read data!\n";
                }
                else {
                    temp += dwBuffer;
                }
                delete[] dwBuffer;
            }
        } while (dwSize > 0);
    }
    if (hiRequest) {
        WinHttpCloseHandle(hiRequest);
    }
    std::wstring result = L"";
    if (temp != "") {
        for (int i = temp.find("\":\"") + 3; i < temp.size() - 3; i++) {
            result += wchar_t(temp[i]);
        }
    }
    return result;
}

//Get the JSON file from third party
void requestData(HINTERNET connectToServer, std::wstring noti) {
    noti += API_KEY;
    HINTERNET hiRequest = WinHttpOpenRequest(connectToServer, L"GET", noti.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    bool hiResult = WinHttpSendRequest(hiRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if (hiResult) {
        hiResult = WinHttpReceiveResponse(hiRequest, NULL);
    }
    std::string result = "";
    DWORD dwSize = 0, dwPull = 0;
    char* dwBuffer;
    if (hiResult) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hiRequest, &dwSize)) {
                std::cout << "Error " << GetLastError() << " query data unavailable!\n";
            }
            dwBuffer = new char[dwSize + 1];
            if (!dwBuffer) {
                std::cout << "Out of memory!\n";
                dwSize = 0;
            }
            else {
                ZeroMemory(dwBuffer, dwSize + 1);
                if (!WinHttpReadData(hiRequest, (LPVOID)dwBuffer, dwSize, &dwPull)) {
                    std::cout << "Error " << GetLastError() << " winhttp can't read data!\n";
                }
                else {
                    result += dwBuffer;
                }
                delete[] dwBuffer;
            }
        } while (dwSize > 0);
    }
    if (!hiResult) {
        std::cout << "Error " << GetLastError() << " has occured!\n";
    }
    if (hiRequest) {
        WinHttpCloseHandle(hiRequest);
    }
    if (result.find("Auth Error:") != -1) {
        API_KEY = takeAPI(connectToServer);
        requestData(connectToServer, noti);
        return;
    }
    time_t t = time(0);
    struct tm* now = localtime(&t);
    std::stringstream ss;
    if (now->tm_mon + 1 < 10) {
        ss << now->tm_year + 1900 << "-0" << now->tm_mon + 1 << '-' << now->tm_mday;
    }
    else {
        ss << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday;
    }
    std::string temp = ss.str();
    std::fstream f(temp + ".txt", std::fstream::app);
    std::cout << result;
    f << result;
    f.close();
}

//Server code
int server() {
    // Initialize Socket
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    WORD version = MAKEWORD(2, 2);

    // Initialize Winsock
    iResult = WSAStartup(version, &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed with error: " << iResult << "\n";
        return 1;
    }

    // Initialize Port
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        std::cout << "getaddrinfo failed with error: " << iResult << "\n";
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << "\n";
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << "\n";
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // Listen for a request from client
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << "\n";
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, nullptr, nullptr);
    if (ClientSocket == INVALID_SOCKET) {
        std::cout << "accept failed with error: " << WSAGetLastError() << "\n";
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            std::cout << "Bytes received: " << iResult << "\n";

            // Echo the buffer back to the sender
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                std::cout << "send failed with error: " << WSAGetLastError() << "\n";
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            std::cout << "Bytes sent: " << iSendResult << "\n";
        }
        else if (iResult == 0)
            std::cout << "Connection closing...\n";
        else {
            std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // Shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        std::cout << "shutdown failed with error: " << WSAGetLastError() << "\n";
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // Cleanup
    closesocket(ClientSocket);
    WSACleanup();
}

//main
int __cdecl main(void){
    DWORD dwSize = 0, dwPull = 0;
    BOOL hiResult = FALSE;
    LPSTR dwBuffer;
    HINTERNET hiSession = NULL, hiRequest = NULL, hiConnect = NULL;
    hiSession = WinHttpOpen(L"WinHTTP Test/2.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hiSession) {
        hiConnect = WinHttpConnect(hiSession, L"vapi.vnappmob.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    }
    requestData(hiConnect, L"//api/v2/gold/doji?api_key=");
    requestData(hiConnect, L"//api/v2/gold/sjc?api_key=");
    requestData(hiConnect, L"//api/v2/gold/pnj?api_key=");
    std::cout << "Update completed!";
    if (hiRequest) {
        WinHttpCloseHandle(hiRequest);
    }
    if (hiConnect) {
        WinHttpCloseHandle(hiConnect);
    }
    if (hiSession) {
        WinHttpCloseHandle(hiSession);
    }
    return 0;
}

