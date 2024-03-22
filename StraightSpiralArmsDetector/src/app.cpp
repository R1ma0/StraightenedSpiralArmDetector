#include "app.hpp"

bool App::OnInit()
{
	if (!wxApp::OnInit()) return false;

	AppMainWindowController* mainController = new AppMainWindowController();
	AppMainWindow* mainWindow = new AppMainWindow(
		"Straight Spiral Arms Detector",
		mainController
	);
    mainController->SetView(mainWindow);
	mainWindow->SetSize(mainWindow->FromDIP(wxSize(800, 600)));
	mainWindow->Center();
	mainWindow->Maximize();
	mainWindow->Show(true);

	return true;
}
