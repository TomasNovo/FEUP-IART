#include "gui.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	IART::gui form;
	Application::Run(%form);
}

