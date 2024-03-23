#include "app.hpp"

App::App()
{
	locale = new wxLocale();
	appConfigurator = new Configurator();
}

App::~App()
{
	delete i18n;
	delete appConfigurator;
	delete amw;
	delete amwc;
}

bool App::OnInit()
{
	if (!wxApp::OnInit()) return false;

	i18n = new I18N(locale, appConfigurator, this->GetAppName());
	ShowLangStatusMessage();
	amwc = new AppMainWindowController();
	amw = new AppMainWindow(_("Spiral galaxy handler"), amwc);

    amwc->SetView(amw);
	amw->SetSize(amw->FromDIP(appConfigurator->GetWindowSize()));
	amw->Center();
	amw->Maximize(appConfigurator->GetMaximize());
	amw->Show(true);

	return true;
}

void App::ShowLangStatusMessage()
{
	LangStatusCode code = i18n->GetLangStatusCode();

	switch (code)
	{
	case LangStatusCode::OK:
		break;
	case LangStatusCode::Unsupported:
		wxMessageBox(
			_(
				"The selected language is unsupported.\n"
				"The default language is set."
			),
			_("Application language"),
			wxICON_INFORMATION
		);
		break;
	case LangStatusCode::Wrong:
		wxMessageBox(
			_(
				"Wrong language has been selected!\n"
				"The default language is set."
			),
			_("Application language"),
			wxICON_WARNING
		);
		break;
	default:
		break;
	}
}
