#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Signin.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Signup
	/// </summary>
	public ref class Signup : public System::Windows::Forms::Form
	{
	public:
		SOCKET ConnectSocket = INVALID_SOCKET;
	public:
		Signup(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		Signup(SOCKET Connect1)
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
		~Signup()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ Signup_username;
	public: System::Windows::Forms::TextBox^ Signup_password;
	private:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Signup_username = (gcnew System::Windows::Forms::TextBox());
			this->Signup_password = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(60, 180);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Register";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Signup::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(33, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Sign up";
			// 
			// Signup_username
			// 
			this->Signup_username->Location = System::Drawing::Point(38, 82);
			this->Signup_username->Name = L"Signup_username";
			this->Signup_username->Size = System::Drawing::Size(189, 20);
			this->Signup_username->TabIndex = 2;
			this->Signup_username->Text = L"Username";
			this->Signup_username->TextChanged += gcnew System::EventHandler(this, &Signup::textBox1_TextChanged);
			// 
			// Signup_password
			// 
			this->Signup_password->Location = System::Drawing::Point(38, 126);
			this->Signup_password->Name = L"Signup_password";
			this->Signup_password->PasswordChar = '*';
			this->Signup_password->Size = System::Drawing::Size(189, 20);
			this->Signup_password->TabIndex = 3;
			this->Signup_password->Text = L"Password";
			this->Signup_password->TextChanged += gcnew System::EventHandler(this, &Signup::textBox2_TextChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(283, 180);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(140, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Or you have an account";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Signup::button2_Click);
			// 
			// Signup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(474, 261);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->Signup_password);
			this->Controls->Add(this->Signup_username);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"Signup";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Signup";
			this->Load += gcnew System::EventHandler(this, &Signup::Signup_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ username = "";
	
		username = Signup_username->Text;
		if (username->Length == 0 || username->Equals("Username")) {
			MessageBox::Show("Please input the Username");
			return;
		}

		String^ password = "";

		password = Signup_password->Text;
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
			MessageBox::Show("Username had been used");
		}
		else if (strcmp(respond, t) == 0) {
			MessageBox::Show("Register successful");
			iResult = send(ConnectSocket, "online", sizeof("online"), 0);
			Signup::Hide();
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Signup_Load(System::Object^ sender, System::EventArgs^ e) {
	int iResult;
	iResult = send(ConnectSocket, "signup", sizeof("signup"), 0);
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	int iResult;
	iResult = send(ConnectSocket, "close", sizeof("close"), 0);
	Signup::Hide();
	Signin^ signin = gcnew Signin(ConnectSocket);
	signin->ShowDialog();
}
};
}
