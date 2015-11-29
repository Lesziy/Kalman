#include "wxGUI.h"
#include <wx/init.h>
/**
	Constructor for wxGUI needs env variables
*/
wxGUI::wxGUI(int argc, char **argv)
{
    wx_ = new App();
    wxApp::SetInstance(wx_);
    wxEntryStart(argc, &argv);
    wx_->CallOnInit();
	wx->OnRun();
	wx->OnExit();
}

wxGUI::~wxGUI()
{
    wxEntryCleanup();
    delete wx_;
}

