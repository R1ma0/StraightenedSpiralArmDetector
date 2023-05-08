#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <fstream>
#include <vector>
#include "tinyxml2.h"

namespace fs = std::filesystem;

namespace processed_data_namespace
{
	struct _ProcessedParameter
	{
		double min;
		double max;
		double step;
		unsigned int getIterRange()
		{
			return (max - min) / step;
		}
	};

	class ProcessedData 
	{
	private:
		_ProcessedParameter binaryThreshValue;
		_ProcessedParameter gaussConst;
		_ProcessedParameter imgCompressPercentage;
		_ProcessedParameter gaussBlockSize;
		void readConfigFile(fs::path);
	public:
		ProcessedData(fs::path);
		unsigned int calcTotalOutputPerFile();
		std::vector<double> getBinaryThreshValueParams();
		std::vector<double> getGaussConstParams();
		std::vector<double> getImgCompressPercentageParams();
		std::vector<double> getGaussBlockSizeParams();
	};
}

#endif
