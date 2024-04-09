#include "src_files_handler.hpp"

SrcFilesData* GetFilesList(wxString dir, std::vector<wxString> formats)
{
	wxArrayString* formatFiles = new wxArrayString();
	wxArrayString allFiles;
	std::size_t filesCount = 0;

	for (auto format{ formats.begin() }; format != formats.end(); format++)
	{
		formatFiles->Empty();
		filesCount += wxDir::GetAllFiles(dir, formatFiles, *format);
		allFiles.insert(allFiles.end(), formatFiles->begin(), formatFiles->end());
	}

	delete formatFiles;

	return new SrcFilesData{ allFiles, filesCount };
}