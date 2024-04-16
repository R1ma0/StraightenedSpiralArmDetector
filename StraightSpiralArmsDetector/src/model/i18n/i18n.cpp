#include "i18n.hpp"

I18N::I18N(
	wxLocale* locale, 
	wxStandardPaths* standardPaths, 
	wxString appName,
	std::string langCode
)
{
	this->locale = locale;
	this->standardPaths = standardPaths;
	this->appName = appName;
	this->langCode = langCode;

	SetLanguage();
}

void I18N::SetLanguage()
{
	if (LANGUAGES.find(langCode) == LANGUAGES.end())
	{
		language = DEFAULT_LANG;
		langStatusCode = LangStatusCode::Wrong;
	}
	else
	{
		language = wxLanguage(LANGUAGES.at(langCode));
		langStatusCode = LangStatusCode::OK;
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
			langStatusCode = LangStatusCode::Wrong;
		}
	}
	else
	{
		language = DEFAULT_LANG;
		tmpLocale = new wxLocale(language);
		langStatusCode = LangStatusCode::Unsupported;
	}

	locale = tmpLocale;
}

void I18N::SetLanguagesPath()
{
	wxString dataDir = standardPaths->GetDataDir();
	fs::path langDir = fs::u8path(std::string(dataDir)).parent_path();
	langDir += "/locale";

	locale->AddCatalogLookupPathPrefix(langDir.c_str());
	locale->AddCatalog(appName);
}