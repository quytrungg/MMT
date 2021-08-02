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
	/// Summary for Main_form
	/// </summary>
	public ref class Main_form : public System::Windows::Forms::Form
	{
	public:
		int sign_in = -1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DataGridView^ Data_Gold;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Kind;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Buy;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Sell;






	public:

		   SOCKET ConnectSocket = INVALID_SOCKET;
	public:
		Main_form(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		Main_form(SOCKET Connect, String^ user)
		{
			InitializeComponent();
			Username->Text = user;
			ConnectSocket = Connect;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Hi;
	protected:
	private: System::Windows::Forms::Label^ Username;
	private: System::Windows::Forms::DateTimePicker^ Date_Month_Year;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ Kind_of_gold;
	private: System::Windows::Forms::Button^ Log_out;
	private: System::Windows::Forms::Button^ Search;


	protected:

	protected:

	protected:

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
			this->Hi = (gcnew System::Windows::Forms::Label());
			this->Username = (gcnew System::Windows::Forms::Label());
			this->Date_Month_Year = (gcnew System::Windows::Forms::DateTimePicker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Kind_of_gold = (gcnew System::Windows::Forms::ComboBox());
			this->Log_out = (gcnew System::Windows::Forms::Button());
			this->Search = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Data_Gold = (gcnew System::Windows::Forms::DataGridView());
			this->Kind = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Buy = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Sell = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Data_Gold))->BeginInit();
			this->SuspendLayout();
			// 
			// Hi
			// 
			this->Hi->AutoSize = true;
			this->Hi->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Hi->Location = System::Drawing::Point(476, 24);
			this->Hi->Name = L"Hi";
			this->Hi->Size = System::Drawing::Size(24, 20);
			this->Hi->TabIndex = 0;
			this->Hi->Text = L"Hi";
			// 
			// Username
			// 
			this->Username->AutoSize = true;
			this->Username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Username->Location = System::Drawing::Point(519, 24);
			this->Username->Name = L"Username";
			this->Username->Size = System::Drawing::Size(57, 20);
			this->Username->TabIndex = 1;
			this->Username->Text = L"label1";
			this->Username->Click += gcnew System::EventHandler(this, &Main_form::Username_Click);
			// 
			// Date_Month_Year
			// 
			this->Date_Month_Year->CalendarFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Date_Month_Year->CustomFormat = L"yyyy-MM-dd";
			this->Date_Month_Year->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Date_Month_Year->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->Date_Month_Year->Location = System::Drawing::Point(74, 197);
			this->Date_Month_Year->MaxDate = System::DateTime(2021, 12, 31, 0, 0, 0, 0);
			this->Date_Month_Year->MinDate = System::DateTime(2021, 1, 1, 0, 0, 0, 0);
			this->Date_Month_Year->Name = L"Date_Month_Year";
			this->Date_Month_Year->Size = System::Drawing::Size(175, 22);
			this->Date_Month_Year->TabIndex = 2;
			this->Date_Month_Year->ValueChanged += gcnew System::EventHandler(this, &Main_form::Date_Month_Year_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(81, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"GOLD";
			this->label1->Click += gcnew System::EventHandler(this, &Main_form::label1_Click);
			// 
			// Kind_of_gold
			// 
			this->Kind_of_gold->FormattingEnabled = true;
			this->Kind_of_gold->Location = System::Drawing::Point(74, 142);
			this->Kind_of_gold->Name = L"Kind_of_gold";
			this->Kind_of_gold->Size = System::Drawing::Size(175, 21);
			this->Kind_of_gold->TabIndex = 4;
			this->Kind_of_gold->SelectedIndexChanged += gcnew System::EventHandler(this, &Main_form::Kind_of_gold_SelectedIndexChanged);
			// 
			// Log_out
			// 
			this->Log_out->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Log_out->Location = System::Drawing::Point(604, 24);
			this->Log_out->Name = L"Log_out";
			this->Log_out->Size = System::Drawing::Size(75, 23);
			this->Log_out->TabIndex = 5;
			this->Log_out->Text = L"Log out";
			this->Log_out->UseVisualStyleBackColor = true;
			this->Log_out->Click += gcnew System::EventHandler(this, &Main_form::Log_out_Click);
			// 
			// Search
			// 
			this->Search->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Search->Location = System::Drawing::Point(86, 253);
			this->Search->Name = L"Search";
			this->Search->Size = System::Drawing::Size(75, 23);
			this->Search->TabIndex = 6;
			this->Search->Text = L"Search";
			this->Search->UseVisualStyleBackColor = true;
			this->Search->Click += gcnew System::EventHandler(this, &Main_form::Search_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(293, 76);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Price";
			this->label2->Click += gcnew System::EventHandler(this, &Main_form::label2_Click);
			// 
			// Data_Gold
			// 
			this->Data_Gold->AllowUserToDeleteRows = false;
			this->Data_Gold->AllowUserToResizeColumns = false;
			this->Data_Gold->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Data_Gold->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Kind, this->Buy,
					this->Sell
			});
			this->Data_Gold->Location = System::Drawing::Point(297, 121);
			this->Data_Gold->Name = L"Data_Gold";
			this->Data_Gold->Size = System::Drawing::Size(343, 155);
			this->Data_Gold->TabIndex = 8;
			this->Data_Gold->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Main_form::Data_Gold_CellContentClick);
			// 
			// Kind
			// 
			this->Kind->HeaderText = L"Kind of gold";
			this->Kind->Name = L"Kind";
			// 
			// Buy
			// 
			this->Buy->HeaderText = L"Buy";
			this->Buy->Name = L"Buy";
			// 
			// Sell
			// 
			this->Sell->HeaderText = L"Sell";
			this->Sell->Name = L"Sell";
			// 
			// Main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(713, 380);
			this->Controls->Add(this->Data_Gold);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Search);
			this->Controls->Add(this->Log_out);
			this->Controls->Add(this->Kind_of_gold);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Date_Month_Year);
			this->Controls->Add(this->Username);
			this->Controls->Add(this->Hi);
			this->Name = L"Main_form";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main_form";
			this->Load += gcnew System::EventHandler(this, &Main_form::Main_form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Data_Gold))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Main_form_Load(System::Object^ sender, System::EventArgs^ e) {
		Kind_of_gold->Items->Add("SJC");
		Kind_of_gold->Items->Add("DOJI");
		Kind_of_gold->Items->Add("PNJ");
		Data_Gold->Rows->Add(5);
	}
	private: System::Void Search_Click(System::Object^ sender, System::EventArgs^ e) {
		
	}
	private: System::Void Log_out_Click(System::Object^ sender, System::EventArgs^ e) {
		int iResult;
		iResult = send(ConnectSocket, "close", sizeof("close"), 0);
		iResult = send(ConnectSocket, "signin", sizeof("signin"), 0);
		sign_in = 1;
		Main_form::Hide();
	}
	private: System::Void Username_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Date_Month_Year_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Kind_of_gold_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void Data_Gold_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
