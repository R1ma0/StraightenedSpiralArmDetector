#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <wx/string.h>
#include <vector>

namespace cts
{
	const std::vector<wxString> IN_FILE_FORMATS{ "*.png", "*.jpg", "*.jpeg" };
	const wxString FILE_FILTERS = wxString(
		_("Images (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg")
	);
}

#endif