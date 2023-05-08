#include "processed_data.h"
#include <iostream>

namespace processed_data_namespace
{
	ProcessedData::ProcessedData(fs::path cfg)
	{
		readConfigFile(cfg);
	}

	void ProcessedData::readConfigFile(fs::path pathToFile)
	{
		std::string skip;
		std::ifstream file(pathToFile);

		if (file.is_open())
		{
			std::getline(file, skip, ':');
			file >> binaryThreshValue.min;
			std::getline(file, skip, ':');
			file >> binaryThreshValue.max;
			std::getline(file, skip, ':');
			file >> binaryThreshValue.step;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> gaussConst.min;
			std::getline(file, skip, ':');
			file >> gaussConst.max;
			std::getline(file, skip, ':');
			file >> gaussConst.step;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> imgCompressPercentage.min;
			std::getline(file, skip, ':');
			file >> imgCompressPercentage.max;
			std::getline(file, skip, ':');
			file >> imgCompressPercentage.step;
			std::getline(file, skip, '$');
			std::getline(file, skip, ':');
			file >> gaussBlockSize.min;
			std::getline(file, skip, ':');
			file >> gaussBlockSize.max;
			std::getline(file, skip, ':');
			file >> gaussBlockSize.step;
			std::getline(file, skip, '$');
		}

		file.close();
	}

	unsigned int ProcessedData::calcTotalOutputPerFile()
	{
		return binaryThreshValue.getIterRange() * 
			   gaussConst.getIterRange() *
			   imgCompressPercentage.getIterRange() *
			   gaussBlockSize.getIterRange();
	}

	std::vector<float> ProcessedData::getBinaryThreshValueParams()
	{
		return std::vector<float> 
		{
			binaryThreshValue.min,
			binaryThreshValue.max,
			binaryThreshValue.step
		};
	}
	std::vector<float> ProcessedData::getGaussConstParams()
	{
		return std::vector<float> 
		{
			gaussConst.min,
			gaussConst.max,
			gaussConst.step
		};
	}
	std::vector<float> ProcessedData::getImgCompressPercentageParams()
	{
		return std::vector<float>
		{
			imgCompressPercentage.min,
			imgCompressPercentage.max,
			imgCompressPercentage.step
		};
	}
	std::vector<float> ProcessedData::getGaussBlockSizeParams()
	{
		return std::vector<float>
		{
			gaussBlockSize.min,
			gaussBlockSize.max,
			gaussBlockSize.step
		};
	}
}
