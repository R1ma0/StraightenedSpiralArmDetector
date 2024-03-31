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
#include "../constants.hpp"

class Configurator
{
private:
	mINI::INIStructure iniStructure;
	std::filesystem::path pathToIni;
	wxStandardPaths* standardPaths;
	bool IsIniFileExist();
	bool ReadIniFile();
	void Configure();
public:
	Configurator();
	~Configurator();
	mINI::INIStructure GetIniData() const { return iniStructure; };
	wxSize GetWindowSize() const;
	std::string GetLanguageCode() const;
	bool GetMaximize() const;
	void CreateDefaultIniFile();
};

#endif