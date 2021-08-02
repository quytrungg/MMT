#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Signin
	/// </summary>
	public ref class Signin : public System::Windows::Forms::Form
	{
	public:
		SOCKET ConnectSocket = INVALID_SOCKET;
	public:
		Signin(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		Signin(SOCKET Connect1)
		{
			InitializeComponent();
			ConnectSocket = Connect1;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Signin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ Signin_username;
	private: System::Windows::Forms::TextBox^ Signin_password;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Signin_username = (gcnew System::Windows::Forms::TextBox());
			this->Signin_password = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(31, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Sign in";
			// 
			// Signin_username
			// 
			this->Signin_username->Location = System::Drawing::Point(36, 82);
			this->Signin_username->Name = L"Signin_username";
			this->Signin_username->Size = System::Drawing::Size(191, 20);
			this->Signin_username->TabIndex = 1;
			this->Signin_username->Text = L"Username";
			this->Signin_username->TextChanged += gcnew System::EventHandler(this, &Signin::Signin_username_TextChanged);
			// 
			// Signin_password
			// 
			this->Signin_password->Location = System::Drawing::Point(36, 127);
			this->Signin_password->Name = L"Signin_password";
			this->Signin_password->PasswordChar = '*';
			this->Signin_password->Size = System::Drawing::Size(191, 20);
			this->Signin_password->TabIndex = 2;
			this->Signin_password->Text = L"Password";
			this->Signin_password->TextChanged += gcnew System::EventHandler(this, &Signin::Signin_password_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(76, 174);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Log in";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Signin::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(239, 174);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(158, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Or you don\'t have an account";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Signin::button2_Click);
			// 
			// Signin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(424, 261);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Signin_password);
			this->Controls->Add(this->Signin_username);
			this->Controls->Add(this->label1);
			this->Name = L"Signin";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Signin";
			this->Load += gcnew System::EventHandler(this, &Signin::Signin_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Signin_Load(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "signin", sizeof("signin"), 0);
	}
private: System::Void Signin_password_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Signin_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = "";

	username = Signin_username->Text;
	if (username->Length == 0 || username->Equals("Username")) {
		MessageBox::Show("Please input the Username");
		return;
	}

	String^ password = "";

	password = Signin_password->Text;
	if (password->Length == 0 || password->Equals("Password")) {
		MessageBox::Show("Please input the Password");
		return;
	}

	int iResult;
	char respond[512];
	char f[] = "0";
	char t[] = "1";

	char* user = new char[username->Length + 1];
	for (int i = 0; i < username->Length; i++) {
		user[i] = username[i];
	}
	user[username->Length] = '\0';
	iResult = send(ConnectSocket, user, (int)strlen(user), 0);

	char* pass = new char[password->Length + 1];
	for (int i = 0; i < password->Length; i++) {
		pass[i] = password[i];
	}
	pass[password->Length] = '\0';
	iResult = send(ConnectSocket, pass, (int)strlen(pass), 0);

	iResult = recv(ConnectSocket, respond, sizeof(respond), 0);
	if (strcmp(respond, f) == 0) {
		MessageBox::Show("Username or password is not correct");
	}
	else if (strcmp(respond, t) == 0) {
		MessageBox::Show("Log in successful");
		iResult = send(ConnectSocket, "online", sizeof("online"), 0);
		Signin::Hide();
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	int iResult;
	iResult = send(ConnectSocket, "close", sizeof("close"), 0);
	Signin::Close();
}
};
}
