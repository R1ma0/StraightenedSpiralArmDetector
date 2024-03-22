#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/stdpaths.h>
#include <filesystem>
#include <string>
#include "../../libs/ini.h"

class Configurator
{
private:
	mINI::INIStructure iniStructure;
	std::filesystem::path pathToIni;
	const std::string DEFAULT_INI_NAME = "settings.ini";
	bool IsIniFileExist();
	bool ReadIniFile();
	void Configure();
public:
	Configurator();
	mINI::INIStructure GetIniData() const { return iniStructure; };
	wxSize GetWindowSize() const;
	std::string GetLanguageCode() const;
	bool GetMaximize() const;
	void CreateDefaultIniFile();
};

#endif