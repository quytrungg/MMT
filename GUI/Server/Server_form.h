#pragma once
#include <thread>
#include <string>
#include <Windows.h>
#include "Help.h"



void Update_Gold();
void Sever_source(System::Object^ obj);
void Server_Run();
void Disconect_All_Server();
void Save();

namespace Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Server_form
	/// </summary>
	public ref class Server_form : public System::Windows::Forms::Form
	{
	public:
		
		
		Server_form(void)
		{
			std::thread update(Update_Gold);
			update.detach();
			std::thread run(Server_Run);
			run.detach();
			
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			Thread^ server_source = gcnew Thread(gcnew ParameterizedThreadStart(&Sever_source));
			server_source->Start(this);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Server_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ Client_status;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Socket_ID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Username;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Status;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Work;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ Disconect_All;
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
			this->Client_status = (gcnew System::Windows::Forms::DataGridView());
			this->Socket_ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Username = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Status = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Work = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->Disconect_All = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Client_status))->BeginInit();
			this->SuspendLayout();
			// 
			// Client_status
			// 
			this->Client_status->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Client_status->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Socket_ID,
					this->Username, this->Status, this->Work
			});
			this->Client_status->Location = System::Drawing::Point(12, 76);
			this->Client_status->Name = L"Client_status";
			this->Client_status->ReadOnly = true;
			this->Client_status->Size = System::Drawing::Size(461, 218);
			this->Client_status->TabIndex = 0;
			this->Client_status->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Server_form::Client_status_CellContentClick);
			// 
			// Socket_ID
			// 
			this->Socket_ID->HeaderText = L"Socket ID";
			this->Socket_ID->Name = L"Socket_ID";
			this->Socket_ID->ReadOnly = true;
			// 
			// Username
			// 
			this->Username->HeaderText = L"Username";
			this->Username->Name = L"Username";
			this->Username->ReadOnly = true;
			// 
			// Status
			// 
			this->Status->HeaderText = L"Status";
			this->Status->Name = L"Status";
			this->Status->ReadOnly = true;
			// 
			// Work
			// 
			this->Work->HeaderText = L"Work";
			this->Work->Name = L"Work";
			this->Work->ReadOnly = true;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Server_form::backgroundWorker1_DoWork);
			// 
			// Disconect_All
			// 
			this->Disconect_All->Location = System::Drawing::Point(493, 106);
			this->Disconect_All->Name = L"Disconect_All";
			this->Disconect_All->Size = System::Drawing::Size(105, 23);
			this->Disconect_All->TabIndex = 1;
			this->Disconect_All->Text = L"Disconect all client";
			this->Disconect_All->UseVisualStyleBackColor = true;
			this->Disconect_All->Click += gcnew System::EventHandler(this, &Server_form::Disconect_All_Click);
			// 
			// Server_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(610, 333);
			this->Controls->Add(this->Disconect_All);
			this->Controls->Add(this->Client_status);
			this->MaximizeBox = false;
			this->Name = L"Server_form";
			this->Text = L"Server_form";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Server_form::Server_form_Closed);
			this->Load += gcnew System::EventHandler(this, &Server_form::Server_form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Client_status))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Server_form_Load(System::Object^ sender, System::EventArgs^ e) {
		Client_status->Rows->Add(15);
	}
	private: System::Void Client_status_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {

	}
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	}
	private: System::Void Disconect_All_Click(System::Object^ sender, System::EventArgs^ e) {
		Disconect_All_Server();
	}
	private: System::Void Server_form_Closed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Save();
		exit(0);
	}
};
}
