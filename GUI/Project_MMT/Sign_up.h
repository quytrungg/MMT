#pragma once

#include "IP_Address.h"



namespace ProjectMMT {

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
		Sign_up(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		/*Sign_up(SOCKET Connect)
		{
			InitializeComponent();
			sign = Connect;
			//
			//TODO: Add the constructor code here
			//
		}*/

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
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ Signup_username;
	private: System::Windows::Forms::TextBox^ Signup_password;
	protected:


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;

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
			this->Signup_username = (gcnew System::Windows::Forms::TextBox());
			this->Signup_password = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(23, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(92, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Sign up";
			this->label1->Click += gcnew System::EventHandler(this, &Sign_up::label1_Click);
			// 
			// Signup_username
			// 
			this->Signup_username->Location = System::Drawing::Point(28, 74);
			this->Signup_username->Name = L"Signup_username";
			this->Signup_username->Size = System::Drawing::Size(203, 20);
			this->Signup_username->TabIndex = 1;
			this->Signup_username->Text = L"Username";
			this->Signup_username->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_username_TextChanged);
			// 
			// Signup_password
			// 
			this->Signup_password->Location = System::Drawing::Point(28, 126);
			this->Signup_password->Name = L"Signup_password";
			this->Signup_password->Size = System::Drawing::Size(203, 20);
			this->Signup_password->TabIndex = 2;
			this->Signup_password->Text = L"Password";
			this->Signup_password->TextChanged += gcnew System::EventHandler(this, &Sign_up::Signup_password_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(54, 184);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Register";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Sign_up::button1_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(275, 184);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(124, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"I am already a member";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Sign_up::button2_Click);
			// 
			// Sign_up
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(480, 261);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Signup_password);
			this->Controls->Add(this->Signup_username);
			this->Controls->Add(this->label1);
			this->Name = L"Sign_up";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		/*String^ username = "";

		username = Signup_username->Text;
		if (username->Length == 0 || username->Equals("Username")) {
			MessageBox::Show("Please input the Username");
			return;
		}

		String^ password = "";

		password = Signup_password->Text;
		if (password->Length == 0 || password->Equals("Username")) {
			MessageBox::Show("Please input the Password");
			return;
		}

		int iResult;
		char respond[512];
		char f[] = "0";

		iResult = send(sign, "signup", 2, 0);

		char* user = new char[username->Length + 1];
		for (int i = 0; i < username->Length; i++) {
			user[i] = username[i];
		}
		user[username->Length] = '\0';
		iResult = send(sign, user, (int)strlen(user), 0);

		char* pass = new char[password->Length + 1];
		for (int i = 0; i < password->Length; i++) {
			pass[i] = password[i];
		}
		pass[password->Length] = '\0';
		iResult = send(sign, pass, (int)strlen(pass), 0);

		iResult = recv(sign, respond, sizeof(respond), 0);
		if (strcmp(respond, f) == 0) {
			MessageBox::Show("Username had been used");
		}
		else {
			MessageBox::Show("Regis successful");
		}*/

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Signup_password_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Signup_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
