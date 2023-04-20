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
			gaussMaxThresh,
			cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
			cv::THRESH_BINARY,
			gaussBlockSize,
			gaussConst
		);

		outImg = resizeImg(outImg, imgCompressPercentage);
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

	void Detectorator::readImg(std::filesystem::path from, cv::Mat& to)
	{
		to = cv::imread(from, cv::IMREAD_GRAYSCALE);
		
		if (to.empty())
		{
			reportFailedOperation(
				"Could not read the image : " + std::string(from), true
			);
		}
	}

	void Detectorator::writeImg(cv::Mat& from, std::filesystem::path to)
	{
		bool isImgWrite {cv::imwrite(to, from)};
		if (!isImgWrite)
		{
			reportFailedOperation(
				"The image was not saved : " + std::string(to), true
			);
		}
	}

	void Detectorator::setGaussMaxThresh(double value)
	{
		if (value < 0. || value > 255.)
		{
			reportFailedOperation(
				"Max threshold value out of range ( 0. <= value <= 255. )", true
			);
		}

		gaussMaxThresh = value;
	}

	void Detectorator::setImgCompressPercentage(double value)
	{
		if (value <= 0. || value > 100.)
		{
			reportFailedOperation(
				"Compression value out of range ( 0. < value <= 100. )", true
			);
		}

		imgCompressPercentage = value;
	}

	void Detectorator::reportFailedOperation(std::string msg, bool close)
	{
		std::cout << "FAILDED. " + msg << std::endl;
		if (close)
			exit(0);
	}
}
