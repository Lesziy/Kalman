#pragma once
#include <wx/glcanvas.h>
#include "GraphicsContext.h"
/**
	Used to display graphics from graphicscontext
	Much huge part of this class is suggested on samples in wxWidgets 3.0.2
*/
class GraphicsCanvas : public wxGLCanvas
{
public:
	GraphicsCanvas(wxWindow *parent);
	
	GraphicsContext &getContext();
private:
	GraphicsContext *graphicsContext;
	/**
		defines behaviour when parent asks it to paint
	*/
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& WXUNUSED(event));
	wxDECLARE_EVENT_TABLE();
	void ResetProjectionMode();
};

