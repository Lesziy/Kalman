#pragma once
#pragma once
#include <wx\glcanvas.h> 
class GraphicsContext : public wxGLContext
{
public:
	GraphicsContext(wxGLCanvas* canvas);
	void draw();
};

