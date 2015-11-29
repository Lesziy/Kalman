#include "GUI.h"
#include <wx\init.h>
GUI::GUI(int argc, char** argv)
{
	app = new App();
	wxApp::SetInstance(app);
	wxEntryStart(argc, argv);
	app->CallOnInit();
}

GUI::~GUI()
{
	wxEntryCleanup();
	delete app;
}

void GUI::run()
{
	app->OnRun();
	app->OnExit();
}
