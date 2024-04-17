#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#ifdef _SSAD_CONFIGURATOR_EXPORTS
#define SSAD_CONFIGURATOR_API __declspec(dllexport)
#else
#define SSAD_CONFIGURATOR_API __declspec(dllimport)
#endif

#include <wx/string.h>
#include <wx/gdicmn.h>
#include <filesystem>
#include <string>
#include "ini.h"

class SSAD_CONFIGURATOR_API Configurator
{
private:
	std::string iniName;
	mINI::INIStructure iniStructure;
	std::filesystem::path pathToIni;
	wxString exePath;
	bool IsIniFileExist();
	bool ReadIniFile();
	void Configure();
public:
	Configurator(std::string, wxString);
	mINI::INIStructure GetIniData() const;
	wxSize GetWindowSize() const;
	std::string GetLanguageCode() const;
	bool GetMaximize() const;
	void CreateDefaultIniFile();
};

#endif