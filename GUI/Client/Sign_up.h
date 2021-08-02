#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Sign_in.h"
#include "Main_form.h"

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Sign_up
	/// </summary>
	public ref class Sign_up : public System::Windows::Forms::Form
	{
	public:
		SOCKET ConnectSocket = INVALID_SOCKET;
	public:
		Sign_up(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		Sign_up(SOCKET Connect)
		{
			InitializeComponent();
			ConnectSocket = Connect;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Sign_up()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ Signup_username;
	protected:
	private: System::Windows::Forms::TextBox^ Signup_password;
	private: System::Windows::Forms::Button^ Register;
	private: System::Windows::Forms::Button^ Transfer_Signin;
	private: System::Windows::Forms::Label^ label1;

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
			this->Signup_username = (gcnew System::Windows::Forms::TextBox());
			this->Signup_password = (gcnew System::Windows::Forms::TextBox());
			this->Register = (gcnew System::Windows::Forms::Button());
			this->Transfer_Signin = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Signup_username
			// 
			this->Signup_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Signup_username->Location = System::Drawing::Point(36, 77);
			this->Signup_username->Name = L"Signup_username";
			this->Signup_username->Size = System::Drawing::Size(177, 22);
			this->Signup_username->TabIndex = 0;
			this->Signup_username->Text = L"Username";
			this->Signup_username->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_username_TextChanged);
			// 
			// Signup_password
			// 
			this->Signup_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Signup_password->Location = System::Drawing::Point(36, 126);
			this->Signup_password->Name = L"Signup_password";
			this->Signup_password->PasswordChar = '*';
			this->Signup_password->Size = System::Drawing::Size(177, 22);
			this->Signup_password->TabIndex = 1;
			this->Signup_password->Text = L"Password";
			this->Signup_password->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_password_TextChanged);
			// 
			// Register
			// 
			this->Register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Register->Location = System::Drawing::Point(60, 179);
			this->Register->Name = L"Register";
			this->Register->Size = System::Drawing::Size(93, 23);
			this->Register->TabIndex = 2;
			this->Register->Text = L"Register";
			this->Register->UseVisualStyleBackColor = true;
			this->Register->Click += gcnew System::EventHandler(this, &Sign_up::Register_Click);
			// 
			// Transfer_Signin
			// 
			this->Transfer_Signin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Transfer_Signin->Location = System::Drawing::Point(223, 179);
			this->Transfer_Signin->Name = L"Transfer_Signin";
			this->Transfer_Signin->Size = System::Drawing::Size(179, 23);
			this->Transfer_Signin->TabIndex = 3;
			this->Transfer_Signin->Text = L"Or you have an account";
			this->Transfer_Signin->UseVisualStyleBackColor = true;
			this->Transfer_Signin->Click += gcnew System::EventHandler(this, &Sign_up::Transfer_Signin_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(36, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Sign up";
			// 
			// Sign_up
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(427, 261);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Transfer_Signin);
			this->Controls->Add(this->Register);
			this->Controls->Add(this->Signup_password);
			this->Controls->Add(this->Signup_username);
			this->MaximizeBox = false;
			this->Name = L"Sign_up";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sign_up";
			this->Load += gcnew System::EventHandler(this, &Sign_up::Sign_up_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Sign_up_Load(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "signup", sizeof("signup"), 0);
	}
	private: System::Void Signup_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Signup_password_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Register_Click(System::Object^ sender, System::EventArgs^ e) {
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
			Sign_up::Hide();
			Main_form^ mainform = gcnew Main_form(ConnectSocket, username);
			mainform->ShowDialog();
		}
	}
	private: System::Void Transfer_Signin_Click(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "close", sizeof("close"), 0);
		Sign_up::Hide();
		Sign_in^ signin = gcnew Sign_in(ConnectSocket);
		signin->ShowDialog();
		if (signin->sign_up == 1) {
			Sign_up::Show();
		}
	}
};
}
