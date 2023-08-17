#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include "aliases.h"
#include "tinyxml2.h"
#include "processed_parameters.h"

namespace fs = std::filesystem;
namespace pp = processed_parameters_namespace;

namespace processed_data_namespace
{
	struct ImgProcessingParameters
	{
		float gaussBlockSize;
		float gaussConst;
		float imgCompressPercentage;
		float binaryThreshValue;
		float processingTime;
		std::string srcPath;
		std::string outPath;
	};

	class ProcessedData 
	{
	private:
		pp::ProcessedParameters binaryThreshValue;
		pp::ProcessedParameters gaussConst;
		pp::ProcessedParameters imgCompressPercentage;
		pp::ProcessedParameters gaussBlockSize;
		std::vector<ImgProcessingParameters> imgProcParams;
		uint totalOutputPerFile;
		uint totalOutput;
		void calcTotalOutputPerFile();
		void calcTotalOutput(uint);
		void readConfigFile(fs::path);
	public:
		ProcessedData(fs::path, uint);
		pp::ProcessedParameters getBinaryThreshValueParams();
		pp::ProcessedParameters getGaussConstParams();
		pp::ProcessedParameters getImgCompressPercentageParams();
		pp::ProcessedParameters getGaussBlockSizeParams();
		uint getTotalOutputPerFile() { return totalOutputPerFile; };
		uint getTotalOutput() { return totalOutput; };
		void saveProcessedParameters(float, float, float, float, float, std::string, std::string);
		void writeProcessedParametersToXML(fs::path);
	};
}

#endif
