#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <vector>

namespace cts
{
	const std::vector<wxString> IN_FILE_FORMATS{ "*.png", "*.jpg", "*.jpeg" };
	const wxString FILE_FILTERS = wxString(
		_("Images (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg")
	);
}

#endif