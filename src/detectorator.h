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
namespace fs = std::filesystem;

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
		void resizeImg(cv::Mat &, double);
		void reportFailedOperation(std::string, bool);
		void performAnOperationWithPixels(PixelsOperation, cv::Mat &);
		double binaryThreshValue;
		double gaussConst; /// Constant subtracted from the mean of weighted mean
		double imgCompressPercentage;
		double threshBinValue;
		int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
		bool isPixelMatchesPatterns(vInt &, PixelPatterns &, cf::CommonFunctions &);
	public:
		void execute(cv::Mat, cv::Mat &);
		void readImg(fs::path, cv::Mat &);
		void writeImg(cv::Mat &, fs::path);
		void setBinaryThreshValue(double);
		void setThreshBinValue(double);
		void setImgCompressPercentage(double);
		void setGaussConst(double value) { gaussConst = value; };
		void setGaussBlockSize(int value) { gaussBlockSize = value; };
		double getBinaryThreshValue() { return binaryThreshValue; };
		double getThreshBinValue() { return threshBinValue; };
		double getImgCompressPercentage() { return imgCompressPercentage; };
		double getGaussConst() { return gaussConst; };
		int getGaussBlockSize() { return gaussBlockSize; };
	};
}

#endif
