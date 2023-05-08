#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace config_namespace
{
	class Config
	{
	private:
		void parseConfigFile(fs::path);
		double minBinaryThreshValue;
		double maxBinaryThreshValue;
		double stepBinaryThreshValue;
		double minGaussConst;
		double maxGaussConst;
		double stepGaussConst;
		double minImgCompressPercentage;
		double maxImgCompressPercentage;
		double stepImgCompressPercentage;
		double minThreshBinValue;
		double maxThreshBinValue;
		double stepThreshBinValue;
		int minGaussBlockSize;
		int maxGaussBlockSize;
		int stepGaussBlockSize;
	public:
		Config(fs::path);
		double getMinBinaryThreshValue() { return minBinaryThreshValue; }
		double getMaxBinaryThreshValue() { return maxBinaryThreshValue; }
		double getStepBinaryThreshValue() { return stepBinaryThreshValue; }
		double getMinGaussConst() { return minGaussConst; };
		double getMaxGaussConst() { return maxGaussConst; };
		double getStepGaussConst() { return stepGaussConst; };
		double getMinImgCompressPercentage() { return minImgCompressPercentage; };
		double getMaxImgCompressPercentage() { return maxImgCompressPercentage; };
		double getStepImgCompressPercentage() { return stepImgCompressPercentage; };
		double getMinThreshBinValue() { return minThreshBinValue; };
		double getMaxThreshBinValue() { return maxThreshBinValue; };
		double getStepThreshBinValue() { return stepThreshBinValue; };
		int getMinGaussBlockSize() { return minGaussBlockSize; };
		int getMaxGaussBlockSize() { return maxGaussBlockSize; };
		int getStepGaussBlockSize() { return stepGaussBlockSize; };
	};
}

#endif
