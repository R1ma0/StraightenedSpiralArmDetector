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

namespace detectorator_namespace
{
	class Detectorator
	{
	private:
		cv::Mat resizeImg(cv::Mat img, double cp);
	public:
		void execute(cv::Mat inImg, cv::Mat& outImg);
	};
}

#endif
