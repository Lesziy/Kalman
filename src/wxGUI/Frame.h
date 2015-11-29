#pragma once
#include <wx/wx.h>
#include "App.h"
class Frame : public wxFrame
{
public:
	Frame();
private:
	void onClose(wxCommandEvent &event);
	wxDECLARE_EVENT_TABLE();
};
enum{ ANYTHING = wxID_HIGHEST + 1};
