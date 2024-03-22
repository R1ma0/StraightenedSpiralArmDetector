#ifndef I18N_H
#define I18N_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/stdpaths.h>
#include <filesystem>
#include <map>
#include "../configurator/configurator.hpp"

namespace fs = std::filesystem;

const std::map<std::string, long> LANGUAGES = {
		{"ru_RU", wxLANGUAGE_RUSSIAN},
		{"en_GB", wxLANGUAGE_ENGLISH}
};

enum class LangStatusCode {OK, Unsupported, Wrong};

class I18N
{
private:
	wxLocale* locale;
	wxLocale* tmpLocale;
	Configurator* configurator;
	wxString appName;
	wxLanguage language;
	LangStatusCode langStatusCode = LangStatusCode::OK;
	const wxLanguage DEFAULT_LANG = wxLANGUAGE_ENGLISH;
	void SetLanguage();
	void SetLanguagesPath();
public:
	I18N(wxLocale*, Configurator*, wxString);
	~I18N();
	wxLanguage GetLanguage() const { return language; };
	LangStatusCode GetLangStatusCode() const { return langStatusCode; };
};

#endif