#include "i18n.hpp"

I18N::I18N(wxLocale* locale, Configurator* configurator, wxString appName)
{
	this->locale = locale;
	this->configurator = configurator;
	this->appName = appName;

	SetLanguage();
}

void I18N::SetLanguage()
{
	std::string langCode = configurator->GetLanguageCode();
	
	if (cts::LANGUAGES.find(langCode) == cts::LANGUAGES.end())
	{
		language = DEFAULT_LANG;
		langStatusCode = cts::LangStatusCode::Wrong;
	}
	else
	{
		language = wxLanguage(cts::LANGUAGES.at(langCode));
		langStatusCode = cts::LangStatusCode::OK;
	}

	if (wxLocale::IsAvailable(language))
	{
		tmpLocale = new wxLocale(language);

		SetLanguagesPath();

		if (!tmpLocale->IsOk())
		{
			language = DEFAULT_LANG;
			delete tmpLocale;
			tmpLocale = new wxLocale(language);
			langStatusCode = cts::LangStatusCode::Wrong;
		}
	}
	else
	{
		language = DEFAULT_LANG;
		tmpLocale = new wxLocale(language);
		langStatusCode = cts::LangStatusCode::Unsupported;
	}

	locale = tmpLocale;
}

void I18N::SetLanguagesPath()
{
	wxStandardPaths* stdPaths = (wxStandardPaths*)&wxStandardPaths::Get();
	wxString dataDir = stdPaths->GetDataDir();
	fs::path langDir = fs::u8path(std::string(dataDir)).parent_path();
	langDir += "/locale";

	locale->AddCatalogLookupPathPrefix(langDir.c_str());
	locale->AddCatalog(appName);
}