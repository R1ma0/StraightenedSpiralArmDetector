/* \file
 * \brief Contains the implementation of core
 *        functions for string displaying
 */
#include "detectorator.h"

namespace detectorator_namespace
{
	/* \brief Performs operations to highlight strings
	 */
	void Detectorator::execute(cv::Mat inImg, cv::Mat& outImg)
	{
		cv::adaptiveThreshold(
			inImg, 
			outImg, 
			255, /// Max threshold 
			cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
			cv::THRESH_BINARY,
			3, /// blockSize
			1 /// c
		);
		outImg = resizeImg(outImg, 20.);
	}

	/* In this function is used cv::INTER_LINEAR method
	 *
	 * \param img Image for resizing
	 * \param cp Image compression power
	 * \return Reduced image
	 */
	cv::Mat Detectorator::resizeImg(cv::Mat img, double cp)
	{
		cv::Mat scaledImg;
		double scaleValue {cp / 100.};
		int width {(int)(img.cols * scaleValue)};
		int height {(int)(img.rows * scaleValue)};
		
		cv::resize(img, scaledImg, cv::Size(width, height), cv::INTER_LINEAR);
		
		return scaledImg;
	}
}
