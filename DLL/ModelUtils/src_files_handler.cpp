#include "pch.h"
#include "src_files_handler.hpp"

void GetFilesList(SrcFilesData* data, wxString dir, std::vector<wxString> formats)
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

	data->files = allFiles;
	data->filesCount = filesCount;

	delete formatFiles;
}