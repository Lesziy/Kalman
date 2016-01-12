#include "wxGUI.h"
#include <wx/init.h>
/**
	Constructor for wxGUI needs env variables
*/
wxGUI::wxGUI(int argc, char **argv)
{
    wx_ = new App();
    wxApp::SetInstance(wx_);
    /** \bug Parametry z maina psują poniższą linijkę */
    wxEntryStart(argc, argv);
    wx_->CallOnInit();
    wx_->OnRun();
}

wxGUI::~wxGUI()
{

    wx_->OnExit();
    wxEntryCleanup();
    delete wx_;
}
