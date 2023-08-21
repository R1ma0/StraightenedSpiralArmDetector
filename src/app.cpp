#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "detectorator.h"

class MyApp : public wxApp
{
	public:
		bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
	public:
		MyFrame();
	private:
		void OnExit(wxCommandEvent &event);
};

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello world!")
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Hello world!!!");

	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent &event)
{
	Close(true);
}
