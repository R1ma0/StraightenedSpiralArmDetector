#include "config.h"

namespace config_namespace
{
	Config::Config(fs::path configFile)
	{
		parseConfigFile(configFile);
	}

	void Config::parseConfigFile(fs::path pathToFile)
	{
		std::string skip;
		std::ifstream file(pathToFile);

		if (file.is_open())
		{
			std::getline(file, skip, ':');
			file >> minBinaryThreshValue;
			std::getline(file, skip, ':');
			file >> maxBinaryThreshValue;
			std::getline(file, skip, ':');
			file >> stepBinaryThreshValue;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> minGaussConst;
			std::getline(file, skip, ':');
			file >> maxGaussConst;
			std::getline(file, skip, ':');
			file >> stepGaussConst;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> minImgCompressPercentage;
			std::getline(file, skip, ':');
			file >> maxImgCompressPercentage;
			std::getline(file, skip, ':');
			file >> stepImgCompressPercentage;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> minThreshBinValue;
			std::getline(file, skip, ':');
			file >> maxThreshBinValue;
			std::getline(file, skip, ':');
			file >> stepThreshBinValue;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> minGaussBlockSize;
			std::getline(file, skip, ':');
			file >> maxGaussBlockSize;
			std::getline(file, skip, ':');
			file >> stepGaussBlockSize;
			std::getline(file, skip, '$');
		}

		file.close();
	}
}
