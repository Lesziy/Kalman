#pragma once
#include <wx/glcanvas.h>
/**
	Used to display graphics from graphicscontext
*/
class GraphicsCanvas : public wxGLCanvas
{
public:
	GraphicsCanvas(wxWindow *parent);
private:
	/**
		defines behaviour when parent asks it to paint
	*/
	void onPaint(wxPaintEvent &event);
	wxDECLARE_EVENT_TABLE();
};

