#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "controller/i_controller.hpp"
#include "controller/app_main_window_controller.hpp"
#include "view/app_main_window.hpp"

class App : public wxApp
{
public:
	bool OnInit() override;
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    AppMainWindowController *mainController = new AppMainWindowController();
	AppMainWindow *mainWindow = new AppMainWindow(
	    "Straight Spiral Arms Detector", 
        mainController
    );
    mainController->SetView(mainWindow);
	mainWindow->SetSize(mainWindow->FromDIP(wxSize(1024, 768)));
	mainWindow->Show(true);

	return true;
}
