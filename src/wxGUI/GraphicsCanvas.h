#pragma once
#include <wx/glcanvas.h>
/**
	Used to display graphics from graphicscontext
	Much part of this class is suggested on samples in wxWidgets 3.0.2
*/
class GraphicsCanvas : public wxGLCanvas
{
public:
	GraphicsCanvas(wxWindow *parent);
private:
	/**
		defines behaviour when parent asks it to paint
	*/
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& WXUNUSED(event));
	wxDECLARE_EVENT_TABLE();
	void ResetProjectionMode();
};

