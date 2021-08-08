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
		int flag = 1;
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
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Sign_up::typeid));
			this->Signup_username = (gcnew System::Windows::Forms::TextBox());
			this->Signup_password = (gcnew System::Windows::Forms::TextBox());
			this->Register = (gcnew System::Windows::Forms::Button());
			this->Transfer_Signin = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Signup_username
			// 
			this->Signup_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Signup_username->Location = System::Drawing::Point(36, 113);
			this->Signup_username->Name = L"Signup_username";
			this->Signup_username->Size = System::Drawing::Size(209, 22);
			this->Signup_username->TabIndex = 0;
			this->Signup_username->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_username_TextChanged);
			// 
			// Signup_password
			// 
			this->Signup_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Signup_password->Location = System::Drawing::Point(36, 168);
			this->Signup_password->Name = L"Signup_password";
			this->Signup_password->PasswordChar = '*';
			this->Signup_password->Size = System::Drawing::Size(209, 22);
			this->Signup_password->TabIndex = 1;
			this->Signup_password->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_password_TextChanged);
			// 
			// Register
			// 
			this->Register->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->Register->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Register->Location = System::Drawing::Point(75, 213);
			this->Register->Name = L"Register";
			this->Register->Size = System::Drawing::Size(93, 32);
			this->Register->TabIndex = 2;
			this->Register->Text = L"Register";
			this->Register->UseVisualStyleBackColor = false;
			this->Register->Click += gcnew System::EventHandler(this, &Sign_up::Register_Click);
			// 
			// Transfer_Signin
			// 
			this->Transfer_Signin->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->Transfer_Signin->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Transfer_Signin->Location = System::Drawing::Point(287, 213);
			this->Transfer_Signin->Name = L"Transfer_Signin";
			this->Transfer_Signin->Size = System::Drawing::Size(179, 32);
			this->Transfer_Signin->TabIndex = 3;
			this->Transfer_Signin->Text = L"Or you have an account";
			this->Transfer_Signin->UseVisualStyleBackColor = false;
			this->Transfer_Signin->Click += gcnew System::EventHandler(this, &Sign_up::Transfer_Signin_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(47, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(121, 34);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Sign up";
			this->label1->Click += gcnew System::EventHandler(this, &Sign_up::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label2->Location = System::Drawing::Point(33, 148);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 18);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Password";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label3->Location = System::Drawing::Point(33, 92);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(85, 18);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Username";
			// 
			// Sign_up
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(536, 281);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Transfer_Signin);
			this->Controls->Add(this->Register);
			this->Controls->Add(this->Signup_password);
			this->Controls->Add(this->Signup_username);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Sign_up";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sign_up";
			this->Activated += gcnew System::EventHandler(this, &Sign_up::Form_Activated);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Sign_up::Sign_up_Closed);
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
			MessageBox::Show("Please input the Username", "Notice",MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		String^ password = "";

		password = Signup_password->Text;
		if (password->Length == 0 || password->Equals("Password")) {
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
			MessageBox::Show("Username had been used", "Notice", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else if (strcmp(respond, t) == 0) {
			MessageBox::Show("Register successful","Success");
			iResult = send(ConnectSocket, "online", sizeof("online"), 0);
			Sign_up::Hide();
			Main_form^ mainform = gcnew Main_form(ConnectSocket, username,0);
			mainform->ShowDialog();
			if (mainform->sign == 1) {
				Sign_up::Show();
			}
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
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Form_Activated(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void Sign_up_Closed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "close", sizeof("close"), 0);
		Sleep(100);
		iResult = send(ConnectSocket, "disconect", sizeof("disconect"), 0);
		exit(0);
	}
};
}
