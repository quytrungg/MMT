#include "IP_Address.h"
#include "Sign_up.h"
#include "Sign_in.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	ProjectMMT::IP_Address frm;
	Application::Run(% frm);
}