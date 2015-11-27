#include "App.h"
#include "Frame.h"



App::App()
{
	graphicsContext = NULL;
}

//IMPLEMENT_APP(App)
bool App::OnInit()
{
	if (!wxApp::OnInit())
	{
		return false;
	}
	new Frame();
	return true;
}

int App::OnExit()
{
	delete graphicsContext;
	return wxApp::OnExit();
}

GraphicsContext & App::getContext(GraphicsCanvas * canvas)
{
	//singleton gcontext 
	GraphicsContext *context;
	if (!graphicsContext)
	{
		graphicsContext = new GraphicsContext(canvas);
	}
	context = graphicsContext;
	graphicsContext->SetCurrent(*canvas);
	return *context;
}