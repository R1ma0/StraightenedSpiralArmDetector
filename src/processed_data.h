#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <fstream>
#include <vector>
#include "tinyxml2.h"

namespace fs = std::filesystem;

namespace processed_data_namespace
{
	struct _ProcessedParameters
	{
		float min;
		float max;
		float step;
		unsigned int getIterRange()
		{
			return (max - min) / step;
		}
	};

	class ProcessedData 
	{
	private:
		_ProcessedParameters binaryThreshValue;
		_ProcessedParameters gaussConst;
		_ProcessedParameters imgCompressPercentage;
		_ProcessedParameters gaussBlockSize;
		void readConfigFile(fs::path);
	public:
		ProcessedData(fs::path);
		unsigned int calcTotalOutputPerFile();
		std::vector<float> getBinaryThreshValueParams();
		std::vector<float> getGaussConstParams();
		std::vector<float> getImgCompressPercentageParams();
		std::vector<float> getGaussBlockSizeParams();
	};
}

#endif
