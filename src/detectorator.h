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
		cv::Mat img;
		void resizeImg(cv::Mat &, float);
		void reportFailedOperation(std::string, bool);
		void performAnOperationWithPixels(cv::Mat &, PixelsOperation);
		float binaryThreshValue;
		float gaussConst; /// Constant subtracted from the mean of weighted mean
		float imgCompressPercentage;
		int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
		bool isPixelMatchesPatterns(vInt &, PixelPatterns &, cf::CommonFunctions &);
	public:
		cv::Mat execute();
		void readImg(fs::path);
		void writeImg(cv::Mat, fs::path);
		void setBinaryThreshValue(float value) { binaryThreshValue = value; };
		void setImgCompressPercentage(float value) { imgCompressPercentage = value; };
		void setGaussConst(float value) { gaussConst = value; };
		void setGaussBlockSize(int value) { gaussBlockSize = value; };
	};
}

#endif
