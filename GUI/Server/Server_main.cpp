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
#include <vector>
#include "rapidjson/document.h"
#include "Server_form.h"
#include "Help.h"

using namespace rapidjson;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "winhttp.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#pragma warning(disable:4996)

//Overall variable
std::wstring API_KEY = L"";

struct Gold {
    std::string Name;
    double Buy;
    double Sell;
};

struct Account {
    std::string username;
    std::string password;
};



std::vector <Account> account;
std::vector <Gold> gold_list;


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
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].status = "sign up";
            break;
        }
    }
    do {
        check = 1;
        memset(username, 0, sizeof(username));
        iResult = recv(ClientSocket, username, sizeof(username), 0);
        if (strcmp(username, "close") == 0 || iResult < 0) {
            return;
        }
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
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].username = username;
            break;
        }
    }
}

void Log_in(SOCKET ClientSocket) {
    int iResult;
    char username[1024];
    char password[1024];
    int check = 1;
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].status = "log in";
            break;
        }
    }
    do {
        check = 1;
        memset(username, 0, sizeof(username));
        iResult = recv(ClientSocket, username, sizeof(username), 0);
        if (strcmp(username, "close") == 0 || iResult < 0) {
            return;
        }
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
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].username = username;
            break;
        }
    }
}

//Take the API from third party
std::wstring takeAPI(HINTERNET connectToServer) {
    std::wstring noti = L"/api/request_api_key?scope=gold";
    std::string temp = "";
    HINTERNET hinRequest = WinHttpOpenRequest(connectToServer, L"GET", noti.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    bool hinResult = WinHttpSendRequest(hinRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    bool hinResponse = WinHttpReceiveResponse(hinRequest, NULL);
    DWORD dwSize = 0, dwPull = 0;
    char* dwBuffer;
    if (hinResponse) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hinRequest, &dwSize)) {
                std::cout << "Error " << GetLastError() << " query data unavailable!\n";
            }
            dwBuffer = new char[dwSize + 1];
            if (!dwBuffer) {
                std::cout << "Out of memory!\n";
                dwSize = 0;
            }
            else {
                ZeroMemory(dwBuffer, dwSize + 1);
                if (!WinHttpReadData(hinRequest, (LPVOID)dwBuffer, dwSize, &dwPull)) {
                    std::cout << "Error " << GetLastError() << " winhttp can't read data!\n";
                }
                else {
                    temp += dwBuffer;
                }
                delete[] dwBuffer;
            }
        } while (dwSize > 0);
    }
    if (hinRequest) {
        WinHttpCloseHandle(hinRequest);
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
    HINTERNET hinRequest = WinHttpOpenRequest(connectToServer, L"GET", noti.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    bool hinResult = WinHttpSendRequest(hinRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    if (hinResult) {
        hinResult = WinHttpReceiveResponse(hinRequest, NULL);
    }
    std::string result = "";
    DWORD dwSize = 0, dwPull = 0;
    char* dwBuffer;
    if (hinResult) {
        do {
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hinRequest, &dwSize)) {
                std::cout << "Error " << GetLastError() << ": query data unavailable!\n";
            }
            dwBuffer = new char[dwSize + 1];
            if (!dwBuffer) {
                std::cout << "Out of memory!\n";
                dwSize = 0;
            }
            else {
                ZeroMemory(dwBuffer, dwSize + 1);
                if (!WinHttpReadData(hinRequest, (LPVOID)dwBuffer, dwSize, &dwPull)) {
                    std::cout << "Error " << GetLastError() << ": winhttp can't read data!\n";
                }
                else {
                    result += dwBuffer;
                }
                delete[] dwBuffer;
            }
        } while (dwSize > 0);
    }
    if (!hinResult) {
        std::cout << "Error " << GetLastError() << " has occured!\n";
    }
    if (hinRequest) {
        WinHttpCloseHandle(hinRequest);
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
        if (now->tm_mday > 10) ss << now->tm_year + 1900 << "-0" << now->tm_mon + 1 << "-" << now->tm_mday;
        else ss << now->tm_year + 1900 << "-0" << now->tm_mon + 1 << "-0" << now->tm_mday;
    }
    else {
        if (now->tm_mday > 10) ss << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday;
        else ss << now->tm_year + 1900 << '-' << now->tm_mon + 1 << "-0" << now->tm_mday;
    }
    std::string temp = ss.str();
    std::fstream f("GoldData/" + temp + ".json", std::fstream::app);
    f << result;
    f.close();
}

int countFileLine(std::string filename) {
    std::fstream f(filename, std::fstream::in);
    if (!f) {
        return -1;
    }
    int n = 0;
    std::string temp;
    while (!f.eof()) {
        std::getline(f, temp, '\n');
        if (temp == "") {
            continue;
        }
        else n += 1;
    }
    f.close();
    return n;
}

void extractgold() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    DWORD dwSize = 0, dwPull = 0;
    BOOL hinResult = FALSE;
    LPSTR dwBuffer;
    HINTERNET hiSession = NULL, hinRequest = NULL, hiConnect = NULL;
    hiSession = WinHttpOpen(L"WinHTTP Test/2.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hiSession) {
        hiConnect = WinHttpConnect(hiSession, L"vapi.vnappmob.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    }
    while (true) {
        requestData(hiConnect, L"//api/v2/gold/doji?api_key=");
        requestData(hiConnect, L"//api/v2/gold/sjc?api_key=");
        requestData(hiConnect, L"//api/v2/gold/pnj?api_key=");
        std::cout << "Update completed: " << now->tm_hour << "h" << now->tm_min << "\n";
        Sleep(1800000);
    }
    if (hinRequest) {
        WinHttpCloseHandle(hinRequest);
    }
    if (hiConnect) {
        WinHttpCloseHandle(hiConnect);
    }
    if (hiSession) {
        WinHttpCloseHandle(hiSession);
    }
}

void trackgold() {
    std::string temp, information;
    do {
        std::cout << "Choose your date (yyyy-mm-dd): ";
        std::getline(std::cin, temp, '\n');

        //Get the latest gold update by count until the last 3 lines
        int n = countFileLine("GoldData/" + temp + ".json");
        std::fstream f("GoldData/" + temp + ".json", std::fstream::in);
        if (!f) {
            if (temp.compare("exit") == 0) return;
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
}

char* Convert_int_to_char(int n) {
    int count = 0;
    for (int i = n; i > 0; i = i / 10) {
        count++;
    }
    char* a = new char[count + 1];
    int r;
    for (int i = 0; i < count; i++) {
        r = n % 10;
        n = n / 10;
        a[count - 1 - i] = r + '0';
    }
    a[count] = '\0';
    return a;
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

char* Convert_double_to_char(double n) {
    int count = 0;
    for (int i = n; i > 0; i = i / 10) {
        count++;
    }
    char* a = new char[count + 2];
    double r;
    for (int i = 0; i < count; i++) {
        r = (int)n % 10;
        n = n / 10;
        a[count - 1 - i] = r + '0';
    }
    a[count] = '\v';
    a[count + 1] = '\0';
    return a;
}

void Main_form(SOCKET ClientSocket) {
    int iResult;
    char gold[1024];
    char date[1024];
    char name[1024];
    char price[1024];
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].status = "online";
            break;
        }
    }
    std::string temp, information;
    do {
        memset(gold, 0, sizeof(gold));
        iResult = recv(ClientSocket, gold, sizeof(gold), 0);
        if (strcmp(gold, "close") == 0 || iResult < 0) {
            for (int i = 0; i < client_list.size(); i++) {
                if (client_list[i].socket_ID == ClientSocket) {
                    client_list[i].username = "";
                    client_list[i].work = "";
                    break;
                }
            }
            return;
        }
        memset(date, 0, sizeof(date));
        iResult = recv(ClientSocket, date, sizeof(date), 0);
        std::string Date(date);
        for (int i = 0; i < client_list.size(); i++) {
            if (client_list[i].socket_ID == ClientSocket) {
                client_list[i].work = "get " + (std::string) gold + " gold data by date " + (std::string) date;
                break;
            }
        }
        int n = countFileLine("GoldData/" + Date + ".json");
        std::fstream f("GoldData/" + Date + ".json", std::fstream::in);
        if (!f) {
            iResult = send(ClientSocket, "0", 2, 0);
            continue;
        }
        for (int i = 0; i < n - 3; i++) {
            std::getline(f, temp, '\n');
        }
        int choice = 0;
        std::string kind(gold);
        if (kind.compare("DOJI") == 0) {
            choice = 1;
        }
        else if (kind.compare("SJC") == 0) {
            choice = 2;
        }
        else if (kind.compare("PNJ") == 0) {
            choice = 3;
        }

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
                        }
                        else {
                            Gold Add;
                            std::string temp_1;
                            std::stringstream ss(m.name.GetString());
                            std::getline(ss, temp_1, '_');
                            std::getline(ss, Add.Name, ':');
                            int check = 1;
                            for (int i = 0; i < gold_list.size(); i++) {
                                if (gold_list[i].Name.compare(Add.Name) == 0) {
                                    check = 0;
                                    gold_list[i].Sell = m.value.GetDouble();
                                    break;
                                }
                            }
                            if (check == 1) {
                                Add.Buy = m.value.GetDouble();
                                gold_list.push_back(Add);
                            }
                        }
                    }
                }
            }
        }
        char* count = Convert_int_to_char(gold_list.size());
        iResult = send(ClientSocket, count, 2, 0);

        for (int i = 0; i < gold_list.size(); i++) {
            char* name = new char[gold_list[i].Name.length() + 1];
            for (int j = 0; j < gold_list[i].Name.length(); j++) {
                name[j] = gold_list[i].Name[j];
            }
            name[gold_list[i].Name.length()] = '\v';
            name[gold_list[i].Name.length() + 1] = '\0';
            iResult = send(ClientSocket, name, (int)strlen(name), 0);
            Sleep(100);

            char* buy = Convert_double_to_char(gold_list[i].Buy);
            iResult = send(ClientSocket, buy, (int)strlen(buy), 0);
            Sleep(100);

            char* sell = Convert_double_to_char(gold_list[i].Sell);
            iResult = send(ClientSocket, sell, (int)strlen(sell), 0);
            Sleep(100);
        }
        gold_list.clear();
        delete[] d;
        f.close();
    } while (iResult > 0);
}

void Client_Connect(SOCKET ClientSocket) {
    int iResult;
    char respond[DEFAULT_BUFLEN];
    do {
        iResult = recv(ClientSocket, respond, DEFAULT_BUFLEN, 0);
        if (strcmp(respond, "signup") == 0) {
            Sign_up(ClientSocket);
        }
        else if (strcmp(respond, "signin") == 0) {
            Log_in(ClientSocket);
        }
        else if (strcmp(respond, "online") == 0) {
            Main_form(ClientSocket);
        }
        else if (strcmp(respond, "disconect") == 0) {
            break;
        }
    } while (iResult > 0);
    for (int i = 0; i < client_list.size(); i++) {
        if (client_list[i].socket_ID == ClientSocket) {
            client_list[i].status = "disconect";
            break;
        }
    }
    std::cout << ClientSocket << " Disconect" << std::endl;
}

void Process(SOCKET ListenSocket) {
    account = Read_File_Account("account.txt");
    SOCKET ClientSocket;
    while (1) {
        ClientSocket = accept(ListenSocket, NULL, NULL);
        Client Add;
        Add.socket_ID = ClientSocket;
        client_list.push_back(Add);
        std::thread connect(Client_Connect, ClientSocket);
        connect.detach();
    }
}

void Update_Gold() {
    _wmkdir(L"GoldData");
    extractgold();
}

void Server_Run() {
    SOCKET ListenSocket = ConectClient();
    Process(ListenSocket);
}

void Save() {
    Write_File_Account(account, "account.txt");
}

delegate void Test(System::Windows::Forms::DataGridView^);

void Update_Client(System::Windows::Forms::DataGridView^ b) {
    for (int i = 0; i < 10; i++) {
        b->Rows[i]->Cells[0]->Value = "";
        b->Rows[i]->Cells[1]->Value = "";
        b->Rows[i]->Cells[2]->Value = "";
        b->Rows[i]->Cells[3]->Value = "";
    }
    for (int i = 0; i < client_list.size(); i++) {
        std::string s = std::to_string(client_list[i].socket_ID);
        System::String^ id = gcnew System::String(s.c_str());
        b->Rows[i]->Cells[0]->Value = id;

        System::String^ username = gcnew System::String(client_list[i].username.c_str());
        b->Rows[i]->Cells[1]->Value = username;

        System::String^ status = gcnew System::String(client_list[i].status.c_str());
        b->Rows[i]->Cells[2]->Value = status;

        System::String^ work = gcnew System::String(client_list[i].work.c_str());
        b->Rows[i]->Cells[3]->Value = work;
    }
}

void DoSomething(System::Object^ obj) {
    Server::Server_form::Form^ form = safe_cast<Server::Server_form::Form^>(obj);
    System::Windows::Forms::DataGridView^ table = safe_cast<System::Windows::Forms::DataGridView^>(form->Controls["Client_status"]);
    Test^ test = gcnew Test(Update_Client);
    while (1) {
        try
        {
            form->Invoke(test, table);
        }
        catch (...)
        {
            //Environment::Exit(0);
        }
        Sleep(1000);
    }
}

void Sever_source(System::Object^ obj) {
    System::Threading::Thread^ status = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(&DoSomething));
    status->Start(obj);
}

void Disconect_All_Server() {
    for (int i = 0; i < client_list.size(); i++) {
        closesocket(client_list[i].socket_ID);
        WSACleanup();
    }
}