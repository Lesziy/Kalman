#include "wxGUI.h"
#include <wx/init.h>

wxGUI::wxGUI()
{
    int nasty_hack = 0;
    char * nasty_hack_2 = "";
    wx_ = new App();
    wxApp::SetInstance(wx_);
    wxEntryStart(nasty_hack, &nasty_hack_2);
    wx_->CallOnInit();
}

wxGUI::~wxGUI()
{
    /*wxEntryCleanup();
    delete wx_;*/
}