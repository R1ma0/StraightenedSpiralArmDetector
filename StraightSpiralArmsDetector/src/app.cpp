#include "app.hpp"

App::App()
{
	standardPaths = (wxStandardPaths*)&wxStandardPaths::Get();
	locale = new wxLocale();

	appConfigurator = new Configurator(
		"settings.ini", 
		standardPaths->GetExecutablePath()
	);
	i18n = new I18N(
		locale,
		standardPaths->GetDataDir(),
		this->GetAppName(),
		appConfigurator->GetLanguageCode()
	);

	ShowLangStatusMessage();
}

App::~App()
{
	wxDELETE(i18n);
	wxDELETE(appConfigurator);
}

bool App::OnInit()
{
	if (!wxApp::OnInit()) return false;

	amwc = new AppMainWindowController(appConfigurator);
	amw = new AppMainWindow(_("Spiral galaxy handler"), amwc);

	amwc->SetView(amw);
	amw->SetSize(amw->FromDIP(appConfigurator->GetWindowSize()));
	amw->Center();
	amw->Maximize(appConfigurator->GetMaximize());
	amw->SetIcon(wxICON(IDB_BITMAP1));
	amw->Show(true);

	return true;
}

void App::ShowLangStatusMessage()
{
	LangStatusCode* code = new LangStatusCode(
		i18n->GetLangStatusCode()
	);

	switch (*code)
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

	delete code;
}
