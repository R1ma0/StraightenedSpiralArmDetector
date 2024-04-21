#ifndef I18N_H
#define I18N_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

typedef std::map<std::string, long> LangMap;

const LangMap LANGUAGES = {
		{"ru_RU", wxLANGUAGE_RUSSIAN},
		{"en_GB", wxLANGUAGE_ENGLISH}
};
const enum class LangStatusCode { OK, Unsupported, Wrong };

class I18N
{
private:
	wxLocale* locale;
	wxLocale* tmpLocale;
	wxString appName;
	wxLanguage language;
	wxString dataDir;
	std::string langCode;
	LangStatusCode langStatusCode = LangStatusCode::OK;
	const wxLanguage DEFAULT_LANG = wxLANGUAGE_ENGLISH;
	void SetLanguage();
	void SetLanguagesPath();
public:
	I18N(wxLocale*, wxString, wxString, std::string);
	wxLanguage GetLanguage() const { return language; };
	LangStatusCode GetLangStatusCode() const { return langStatusCode; };
};

#endif