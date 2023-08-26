#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "frames/AppMainWindow.h"

class App : public wxApp
{
public:
	bool OnInit() override;
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	AppMainWindow *mainWindow = new AppMainWindow("Detectorator of strings of galaxies");
	mainWindow->Show(true);
	return true;
}