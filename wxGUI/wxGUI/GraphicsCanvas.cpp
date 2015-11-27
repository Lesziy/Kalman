#include "GraphicsCanvas.h"
#include "GraphicsContext.h"
#include <wx\wxprec.h>
#include <wx/wx.h>
#include "App.h"

GraphicsCanvas::GraphicsCanvas(wxWindow *parent) : wxGLCanvas(parent,wxID_ANY,NULL,wxDefaultPosition,wxDefaultSize,wxNO_FULL_REPAINT_ON_RESIZE)
{ }


void GraphicsCanvas::onPaint(wxPaintEvent & event)
{
	// TODO doesn't use it but need it, i. e. will cause problems and need to be changed with sthng
	wxPaintDC(this);
	const wxSize clientSize = GetClientSize();
	//declaration of application
	wxDECLARE_APP(App);
	//resizing canvas
	GraphicsContext& context = wxGetApp().getContext(this);
	glViewport(0, 0, clientSize.x, clientSize.y);

	context.draw();
	SwapBuffers();
}

wxBEGIN_EVENT_TABLE(GraphicsCanvas, wxGLCanvas)
	EVT_PAINT(GraphicsCanvas::onPaint)
wxEND_EVENT_TABLE()

