#include "configurator.hpp"

Configurator::Configurator()
{
	Configure();
}

Configurator::~Configurator()
{
	delete standardPaths;
}

void Configurator::Configure()
{
	if (!IsIniFileExist())
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
	standardPaths = (wxStandardPaths*)&wxStandardPaths::Get();
	wxString exePath = standardPaths->GetExecutablePath();

	pathToIni = std::filesystem::u8path(std::string(exePath)).parent_path();
	pathToIni += "/" + cts::DEFAULT_INI_NAME;

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

std::string Configurator::GetLanguageCode() const
{
	return iniStructure.get("locale").get("language");
}

bool Configurator::GetMaximize() const
{
	return iniStructure.get("window").get("maximize") == "true" ? true : false;
}

void Configurator::CreateDefaultIniFile()
{
	mINI::INIFile file(pathToIni.u8string());

	iniStructure["locale"]["language"] = "en_GB";

	iniStructure["window"]["width"] = "800";
	iniStructure["window"]["height"] = "600";
	iniStructure["window"]["maximize"] = "false";

	file.generate(iniStructure, true);
}