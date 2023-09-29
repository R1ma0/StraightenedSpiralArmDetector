#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "view/app_main_window.hpp"

class App : public wxApp
{
public:
	bool OnInit() override;
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	AppMainWindow *mainWindow = new AppMainWindow(
	    "Straight Spiral Arms Detector"
	);

	mainWindow->SetSize(mainWindow->FromDIP(wxSize(1024, 768)));
	mainWindow->Show(true);

	return true;
}
