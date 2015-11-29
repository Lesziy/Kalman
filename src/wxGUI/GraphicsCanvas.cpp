#include "GraphicsCanvas.h"
#include <wx/wxprec.h>
#include <wx/wx.h>
#include "App.h"

GraphicsCanvas::GraphicsCanvas(wxWindow *parent) : wxGLCanvas(parent,wxID_ANY,NULL,wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE)
{
	graphicsContext = NULL;
}
GraphicsContext &GraphicsCanvas::getContext()
{
	if (!graphicsContext)
	{
		graphicsContext = new GraphicsContext(this);
		graphicsContext->SetCurrent(*this);
	}
	return *graphicsContext;
}

void GraphicsCanvas::onPaint(wxPaintEvent & event)
{
	// TODO doesn't use it but need it, i. e. will cause problems and need to be changed with sthng
	wxPaintDC(this);
	const wxSize clientSize = GetClientSize();
	GraphicsContext & context = getContext();
	//resizing canvas
	glViewport(0, 0, clientSize.x, clientSize.y);

	context.draw();
	SwapBuffers();
}

wxBEGIN_EVENT_TABLE(GraphicsCanvas, wxGLCanvas)
	EVT_PAINT(GraphicsCanvas::onPaint)
wxEND_EVENT_TABLE()

