#pragma once
#include <wx/wx.h>
#include "GraphicsContext.h"
#include "GraphicsCanvas.h"
#include <thread>
class App : public wxApp
{
public:
	bool OnInit();
	int OnExit();
private:
	//std::thread *t;
};

