

#include "Signup.h"

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#pragma comment (lib, "Ws2_32.lib")

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ txtIPAddress;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->txtIPAddress = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(101, 82);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// txtIPAddress
			// 
			this->txtIPAddress->Location = System::Drawing::Point(45, 46);
			this->txtIPAddress->Name = L"txtIPAddress";
			this->txtIPAddress->Size = System::Drawing::Size(202, 20);
			this->txtIPAddress->TabIndex = 1;
			this->txtIPAddress->Text = L"Input the IP Address";
			this->txtIPAddress->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->txtIPAddress->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 153);
			this->Controls->Add(this->txtIPAddress);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"IP Address";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ IP_Address = "";

		IP_Address = txtIPAddress->Text;
		if (IP_Address->Length == 0 || IP_Address->Equals("Input the IP Address")) {
			MessageBox::Show("Please input the IP Adress");
			return;
		}


		WSADATA wsaData;
		SOCKET ConnectSocket = INVALID_SOCKET;
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;
		int iResult;

		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);


		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		char* Address = new char[IP_Address->Length + 1];
		for (int i = 0; i < IP_Address->Length; i++) {
			Address[i] = IP_Address[i];
		}
		Address[IP_Address->Length] = '\0';

		iResult = getaddrinfo(Address, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			MessageBox::Show("getaddrinfo failed with error ");
			WSACleanup();
			return;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				MessageBox::Show("socket failed with error");
				WSACleanup();
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
			MessageBox::Show("Unable to connect to server");
			WSACleanup();
			return;
		}
		else {
			MessageBox::Show("Connect success");
			MyForm::Hide();
			Signup^ signup = gcnew Signup(ConnectSocket);
			signup->ShowDialog();
		}
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
