#pragma once
#include <wx/wx.h>
#include "Frame.h"
#include <thread>
class App : public wxApp
{
public:
	bool OnInit();
	int OnExit();
private:
	//Frame *frame;
	//std::thread *t;
};

