#pragma once
#include <wx/wx.h>
#include "GraphicsContext.h"
#include "GraphicsCanvas.h"
#include "Frame.h"
#include <thread>
class App : public wxApp
{
public:
	bool OnInit();
	int OnExit();
	
	GraphicsContext &getContext(GraphicsCanvas *canvas);
private:
	GraphicsContext *graphicsContext;
	//Frame *frame;
	//std::thread *t;
};

