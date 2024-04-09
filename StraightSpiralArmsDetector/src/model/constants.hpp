#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <map>
#include <string>
#include <vector>

namespace cts
{
	typedef std::map<std::string, long> LangMap;

	const LangMap LANGUAGES = {
			{"ru_RU", wxLANGUAGE_RUSSIAN},
			{"en_GB", wxLANGUAGE_ENGLISH}
	};
	const std::string DEFAULT_INI_NAME = "settings.ini";
	const std::vector<wxString> IN_FILE_FORMATS{ "*.png", "*.jpg", "*.jpeg" };
	const wxString FILE_FILTERS = wxString(
		_("Images (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg")
	);
	const enum class LangStatusCode { OK, Unsupported, Wrong };
}

#endif