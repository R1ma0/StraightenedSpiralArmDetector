#include "app.hpp"

App::App()
{
	appConfigurator = new Configurator();
}

App::~App()
{
	delete appConfigurator;
	delete amw;
	delete amwc;
}

bool App::OnInit()
{
	if (!wxApp::OnInit()) return false;

	amwc = new AppMainWindowController();
	amw = new AppMainWindow("Straight Spiral Arms Detector", amwc);
    amwc->SetView(amw);
	amw->SetSize(amw->FromDIP(appConfigurator->GetWindowSize()));
	amw->Center();
	amw->Maximize(appConfigurator->GetMaximize());
	amw->Show(true);

	return true;
}
