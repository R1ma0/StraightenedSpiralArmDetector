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
#include <iostream>
#include <filesystem>
#include <cstdlib>

namespace detectorator_namespace
{
	class Detectorator
	{
	private:
		cv::Mat resizeImg(cv::Mat img, double cp);
		void reportFailedOperation(std::string msg, bool close);
		double gaussMaxThresh;
		double gaussConst; /// Constant subtracted from the mean of weighted mean
		double imgCompressPercentage;
		int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
	public:
		void readImg(std::filesystem::path from, cv::Mat& to);
		void writeImg(cv::Mat& from, std::filesystem::path to);
		void setImgCompressPercentage(double value);
		double getImgCompressPercentage() { return imgCompressPercentage; };
		void setGaussMaxThresh(double value);
		double getGaussMaxThresh() { return gaussMaxThresh; };
		void setGaussConst(double value) { gaussConst = value; };
		double getGaussConst() { return gaussConst; };
		void setGaussBlockSize(int value) { gaussBlockSize = value; };
		int getGaussBlockSize() { return gaussBlockSize; };
		void execute(cv::Mat inImg, cv::Mat& outImg);
	};
}

#endif
