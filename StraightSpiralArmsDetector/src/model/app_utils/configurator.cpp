#include "configurator.hpp"

Configurator::Configurator()
{
	Configure();
}

void Configurator::Configure()
{
	bool isIniExist = IsIniFileExist();

	if (!isIniExist)
	{
		CreateDefaultIniFile();
	}
	else
	{
		ReadIniFile();
	}
}

bool Configurator::IsIniFileExist()
{
	wxStandardPaths* standardPaths = (wxStandardPaths*)&wxStandardPaths::Get();
	wxString exePath = standardPaths->GetExecutablePath();

	pathToIni = std::filesystem::u8path(std::string(exePath)).parent_path();
	pathToIni += "/" + DEFAULT_INI_NAME;

	return std::filesystem::exists(pathToIni);
}

bool Configurator::ReadIniFile()
{
	mINI::INIFile file(pathToIni.u8string());

	return file.read(iniStructure);
}

wxSize Configurator::GetWindowSize() const
{
	return wxSize(
		std::stoi(iniStructure.get("window").get("width")),
		std::stoi(iniStructure.get("window").get("height"))
	);
}

bool Configurator::GetMaximize() const
{
	return iniStructure.get("window").get("maximize") == "true" ? true : false;
}

void Configurator::CreateDefaultIniFile()
{
	mINI::INIFile file(pathToIni.u8string());

	iniStructure["window"]["width"] = "800";
	iniStructure["window"]["height"] = "600";
	iniStructure["window"]["maximize"] = "false";

	file.generate(iniStructure, true);
}