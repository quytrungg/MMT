#pragma once

#include "Main_form.h"
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Sign_in
	/// </summary>
	public ref class Sign_in : public System::Windows::Forms::Form
	{
	public:
		int sign_up = -1;
	private: System::Windows::Forms::Label^ label1;
	public:
	private: System::Windows::Forms::Label^ label2;
		   SOCKET ConnectSocket = INVALID_SOCKET;
	public:
		Sign_in(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		Sign_in(SOCKET Connect1)
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
		~Sign_in()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Log_in;
	private: System::Windows::Forms::Button^ Transfer_Signup;
	private: System::Windows::Forms::Label^ Text1;
	private: System::Windows::Forms::TextBox^ Signin_username;
	private: System::Windows::Forms::TextBox^ Signin_password;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Sign_in::typeid));
			this->Log_in = (gcnew System::Windows::Forms::Button());
			this->Transfer_Signup = (gcnew System::Windows::Forms::Button());
			this->Text1 = (gcnew System::Windows::Forms::Label());
			this->Signin_username = (gcnew System::Windows::Forms::TextBox());
			this->Signin_password = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Log_in
			// 
			this->Log_in->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->Log_in->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Log_in->Location = System::Drawing::Point(78, 232);
			this->Log_in->Name = L"Log_in";
			this->Log_in->Size = System::Drawing::Size(93, 30);
			this->Log_in->TabIndex = 0;
			this->Log_in->Text = L"Log in";
			this->Log_in->UseVisualStyleBackColor = false;
			this->Log_in->Click += gcnew System::EventHandler(this, &Sign_in::Log_in_Click);
			// 
			// Transfer_Signup
			// 
			this->Transfer_Signup->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->Transfer_Signup->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Transfer_Signup->Location = System::Drawing::Point(282, 232);
			this->Transfer_Signup->Name = L"Transfer_Signup";
			this->Transfer_Signup->Size = System::Drawing::Size(217, 30);
			this->Transfer_Signup->TabIndex = 1;
			this->Transfer_Signup->Text = L"Or you don\'t have an account";
			this->Transfer_Signup->UseVisualStyleBackColor = false;
			this->Transfer_Signup->Click += gcnew System::EventHandler(this, &Sign_in::Transfer_Signup_Click);
			// 
			// Text1
			// 
			this->Text1->AutoSize = true;
			this->Text1->BackColor = System::Drawing::Color::Transparent;
			this->Text1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text1->ForeColor = System::Drawing::SystemColors::Window;
			this->Text1->Location = System::Drawing::Point(46, 38);
			this->Text1->Name = L"Text1";
			this->Text1->Size = System::Drawing::Size(116, 34);
			this->Text1->TabIndex = 2;
			this->Text1->Text = L"Sign in";
			// 
			// Signin_username
			// 
			this->Signin_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Signin_username->Location = System::Drawing::Point(31, 113);
			this->Signin_username->Name = L"Signin_username";
			this->Signin_username->Size = System::Drawing::Size(225, 24);
			this->Signin_username->TabIndex = 3;
			this->Signin_username->TextChanged += gcnew System::EventHandler(this, &Sign_in::Signin_username_TextChanged);
			// 
			// Signin_password
			// 
			this->Signin_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Signin_password->Location = System::Drawing::Point(31, 169);
			this->Signin_password->Name = L"Signin_password";
			this->Signin_password->PasswordChar = '*';
			this->Signin_password->Size = System::Drawing::Size(225, 24);
			this->Signin_password->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label1->Location = System::Drawing::Point(28, 92);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 18);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Username";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::HighlightText;
			this->label2->Location = System::Drawing::Point(28, 148);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 18);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Password";
			// 
			// Sign_in
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(541, 291);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Signin_password);
			this->Controls->Add(this->Signin_username);
			this->Controls->Add(this->Text1);
			this->Controls->Add(this->Transfer_Signup);
			this->Controls->Add(this->Log_in);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Sign_in";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sign in";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Sign_in::Sign_in_Closed);
			this->Load += gcnew System::EventHandler(this, &Sign_in::Sign_in_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Sign_in_Load(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "signin", sizeof("signin"), 0);
		
	}
	private: System::Void Log_in_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ username = "";

		username = Signin_username->Text;
		if (username->Length == 0) {
			MessageBox::Show("Please input the Username", "Notice", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		String^ password = "";

		password = Signin_password->Text;
		if (password->Length == 0) {
			MessageBox::Show("Please input the Password", "Notice", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
			MessageBox::Show("Username or password is not correct", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (strcmp(respond, t) == 0) {
			MessageBox::Show("Log in successful","Success");
			iResult = send(ConnectSocket, "online", sizeof("online"), 0);
			Sign_in::Hide();
			Main_form^ mainform = gcnew Main_form(ConnectSocket, username,1);
			mainform->ShowDialog();
			if (mainform->sign == 1) {
				Sign_in::Show();
			}
		}
	}
	private: System::Void Transfer_Signup_Click(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "close", sizeof("close"), 0);
		iResult = send(ConnectSocket, "signup", sizeof("signup"), 0);
		sign_up = 1;
		Sign_in::Hide();
	}
	private: System::Void Signin_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Text1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Leave(System::Object^ sender, System::EventArgs^ e) {
	
}
private: System::Void Sign_in_Closed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	int iResult;
	iResult = send(ConnectSocket, "close", sizeof("close"), 0);
	Sleep(100);
	iResult = send(ConnectSocket, "disconect", sizeof("disconect"), 0);
	exit(0);
}
};
}
