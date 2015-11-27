#include "Frame.h"
#include "GraphicsCanvas.h"
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_CLOSE, Frame::onClose)
wxEND_EVENT_TABLE()

Frame::Frame() : wxFrame(NULL, wxID_ANY, wxT("Kalman"))
{
	//create Canvas that have reference to this frame so it knows what and when to do
	new GraphicsCanvas(this);
	//drop-down menu with kinda option separator and close option
	wxMenu *sample = new wxMenu;
	sample->Append(ANYTHING, wxT("Sample Option"));
	sample->AppendSeparator();
	sample->Append(wxID_CLOSE);

	//menu bar on top of the window
	wxMenuBar *sampleBar = new wxMenuBar;
	sampleBar->Append(sample, wxT("&Option"));
	SetMenuBar(sampleBar);
	//status bar with info on the botom of the window
	CreateStatusBar();
	SetClientSize(666, 666);//sry for satan
	Show();

	static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
	wxLogStatus("Double-buffered display %s supported",
		wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");
}

void Frame::onClose(wxCommandEvent & event)
{
	Close(true);
}


