#ifndef SRC_FILE_HANDLER_H
#define SRC_FILE_HANDLER_H

#include <wx/string.h>
#include <wx/dir.h>
#include <vector>
#include "model_utils.hpp"

struct SSAD_MODEL_UTILS_API SrcFilesData
{
	wxArrayString files;
	std::size_t filesCount;
};

void SSAD_MODEL_UTILS_API GetFilesList(SrcFilesData*, wxString, std::vector<wxString>);

#endif