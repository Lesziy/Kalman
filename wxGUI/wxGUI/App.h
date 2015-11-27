#pragma once
#include <wx\wx.h>
#include "GraphicsContext.h"
#include "GraphicsCanvas.h"
class App : public wxApp
{
public:
	App();
	GraphicsContext& getContext(GraphicsCanvas *canvas);
	bool OnInit();
	int OnExit();
private:
	GraphicsContext *graphicsContext;
};

