#pragma once
#include <wx/glcanvas.h>
#include "App.h"
#include "GraphicsContext.h"
/**
	Used to display graphics from graphicscontext
*/
class GraphicsCanvas : public wxGLCanvas
{
public:
	GraphicsCanvas(wxWindow *parent);
	GraphicsContext &getContext();
private:
	/**
		defines behaviour when parent asks it to paint
	*/
	GraphicsContext *graphicsContext;
	void onPaint(wxPaintEvent &event);
	wxDECLARE_EVENT_TABLE();
};

