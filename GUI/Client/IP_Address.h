#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Sign_up.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#pragma comment (lib, "Ws2_32.lib")

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for IP_Address
	/// </summary>
	public ref class IP_Address : public System::Windows::Forms::Form
	{
	public:
		IP_Address(void)
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
		~IP_Address()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ IP;
	private: System::Windows::Forms::Button^ Connect;
	private: System::Windows::Forms::Label^ label1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(IP_Address::typeid));
			this->IP = (gcnew System::Windows::Forms::TextBox());
			this->Connect = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// IP
			// 
			this->IP->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->IP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IP->Location = System::Drawing::Point(53, 135);
			this->IP->Name = L"IP";
			this->IP->Size = System::Drawing::Size(180, 24);
			this->IP->TabIndex = 0;
			this->IP->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->IP->TextChanged += gcnew System::EventHandler(this, &IP_Address::IP_TextChanged);
			// 
			// Connect
			// 
			this->Connect->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Connect->Location = System::Drawing::Point(90, 176);
			this->Connect->Name = L"Connect";
			this->Connect->Size = System::Drawing::Size(102, 31);
			this->Connect->TabIndex = 1;
			this->Connect->Text = L"Connect";
			this->Connect->UseVisualStyleBackColor = true;
			this->Connect->Click += gcnew System::EventHandler(this, &IP_Address::Connect_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Location = System::Drawing::Point(53, 101);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(180, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Input the IP Address";
			// 
			// IP_Address
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Connect);
			this->Controls->Add(this->IP);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"IP_Address";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"IP Address";
			this->Load += gcnew System::EventHandler(this, &IP_Address::IP_Address_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void IP_Address_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}
	private: System::Void IP_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Connect_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ IP_Address = "";

		IP_Address = IP->Text;
		if (IP_Address->Length == 0 || IP_Address->Equals("Input the IP Address")) {
			MessageBox::Show("Please input the IP Adress","Error",MessageBoxButtons::OK,MessageBoxIcon::Question);
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
			MessageBox::Show("Getaddrinfo failed with error ", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			WSACleanup();
			return;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				MessageBox::Show("Socket failed with error", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
			MessageBox::Show("Unable to connect to server", "Error", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			WSACleanup();
			return;
		}
		else {
			MessageBox::Show("Connect success", "Success", MessageBoxButtons::OK);
			IP_Address::Hide();
			Sign_up^ signup = gcnew Sign_up(ConnectSocket);
			signup->ShowDialog();
		}
	}
	private: System::Void Form_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		
	}
	};
}
