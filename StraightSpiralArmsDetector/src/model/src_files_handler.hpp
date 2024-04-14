#ifndef SRC_FILE_HANDLER_H
#define SRC_FILE_HANDLER_H

#include <wx/wxprec.h>
#include <wx/dir.h>
#include <vector>

struct SrcFilesData
{
	wxArrayString files;
	std::size_t filesCount;
};

SrcFilesData* GetFilesList(wxString, std::vector<wxString>);

#endif