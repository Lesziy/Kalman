#include "GraphicsCanvas.h"
#include "App.h"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <iostream>
GraphicsCanvas::GraphicsCanvas(wxWindow *parent) : wxGLCanvas(parent,wxID_ANY,NULL,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{ 
	graphicsContext = new GraphicsContext(this);
}

GraphicsContext &GraphicsCanvas::getContext()
{
	if (!graphicsContext)
	{
		graphicsContext = new GraphicsContext(this);
	}
	//hotfix 01.12.2015
	#ifndef _WIN32 
	graphicsContext->SetCurrent(*this);
	#else	
	graphicsContext->SetCurrent(this);
	#endif	
	return *graphicsContext;
}
void GraphicsCanvas::OnPaint(wxPaintEvent & event)
{
	//getting context to draw on canvas
	int w, h;
	GetClientSize(&w, &h);
	glViewport(0, 0, (GLint) w, (GLint) h);
	graphicsContext->draw();
	SwapBuffers();
}

void GraphicsCanvas::OnSize(wxSizeEvent& WXUNUSED(event))
{
	//std::cout<<"size changing!!!!!\n";
    // Reset the OpenGL view aspect.
    // This is OK only because there is only one canvas that uses the context.
    // See the cube sample for that case that multiple canvases are made current with one context.
    ResetProjectionMode();
}

void GraphicsCanvas::ResetProjectionMode()
{
    if ( !IsShownOnScreen() )
        return;

    // This is normally only necessary if there is more than one wxGLCanvas
    // or more than one wxGLContext in the application.
    //SetCurrent(*m_glRC);

    int w, h;
    GetClientSize(&w, &h);

    // It's up to the application code to update the OpenGL viewport settings.
    // In order to avoid extensive context switching, consider doing this in
    // OnPaint() rather than here, though.
    glViewport(0, 0, (GLint) w, (GLint) h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 10.0f);
}
void GraphicsCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
    // Do nothing, to avoid flashing on MSW
}
wxBEGIN_EVENT_TABLE(GraphicsCanvas, wxGLCanvas)
	EVT_PAINT(GraphicsCanvas::OnPaint)
	//EVT_SIZE(GraphicsCanvas::OnSize)
wxEND_EVENT_TABLE()

