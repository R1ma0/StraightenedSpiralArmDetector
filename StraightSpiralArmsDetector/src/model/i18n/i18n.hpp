#ifndef I18N_H
#define I18N_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/stdpaths.h>
#include <filesystem>
#include "../configurator/configurator.hpp"
#include "../constants.hpp"

namespace fs = std::filesystem;

class I18N
{
private:
	wxLocale* locale;
	wxLocale* tmpLocale;
	Configurator* configurator;
	wxString appName;
	wxLanguage language;
	cts::LangStatusCode langStatusCode = cts::LangStatusCode::OK;
	const wxLanguage DEFAULT_LANG = wxLANGUAGE_ENGLISH;
	void SetLanguage();
	void SetLanguagesPath();
public:
	I18N(wxLocale*, Configurator*, wxString);
	~I18N();
	wxLanguage GetLanguage() const { return language; };
	cts::LangStatusCode GetLangStatusCode() const { return langStatusCode; };
};

#endif