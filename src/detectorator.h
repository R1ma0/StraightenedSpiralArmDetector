/* \file
 * \brief Contains the definition of core
 *        functions for string displaying
 *
 * This file contains a definitions of a set of tools
 * for displaying of strings of galaxies
 */
#ifndef DETECTORATOR_H
#define DETECTORATOR_H

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <cstdlib>
#include "zhang_suen.h"
#include "aliases.h"

namespace zs = zhang_suen_namespace;

namespace detectorator_namespace
{
	enum class PixelsOperation {Add, Remove};
	struct PixelPatterns
	{
		std::vector<vInt> composite;
		vInt compositeSum;
		vInt simple;
	};

	class Detectorator
	{
	private:
		double binaryThreshMaxThreshValue;
		double binaryThreshValue;
		double gaussMaxThresh;
		double gaussConst; /// Constant subtracted from the mean of weighted mean
		double imgCompressPercentage;
		double threshBinValue;
		int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
		void resizeImg(cv::Mat &, double);
		void reportFailedOperation(std::string, bool);
		void performAnOperationWithPixels(PixelsOperation, cv::Mat &);
		bool isPixelMatchesPatterns(vInt &, PixelPatterns &, cf::CommonFunctions &);
	public:
		void execute(cv::Mat, cv::Mat &);
		void readImg(std::filesystem::path, cv::Mat &);
		void writeImg(cv::Mat &, std::filesystem::path);
		void setBinaryThreshValue(double);
		double getBinaryThreshValue() { return binaryThreshValue; };
		void setBinaryThreshMaxThreshValue(double);
		double getBinaryThreshMaxThreshValue() { return binaryThreshMaxThreshValue; };
		void setThreshBinValue(double);
		double getThreshBinValue() { return threshBinValue; };
		void setImgCompressPercentage(double);
		double getImgCompressPercentage() { return imgCompressPercentage; };
		void setGaussMaxThresh(double);
		double getGaussMaxThresh() { return gaussMaxThresh; };
		void setGaussConst(double value) { gaussConst = value; };
		double getGaussConst() { return gaussConst; };
		void setGaussBlockSize(int value) { gaussBlockSize = value; };
		int getGaussBlockSize() { return gaussBlockSize; };
	};
}

#endif
