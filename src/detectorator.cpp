#include "detectorator.h"

namespace detectorator_namespace
{
	cv::Mat Detectorator::execute(cv::Mat image)
	{
		return resizeImg(image, imgCompressRatio);
	}

	void Detectorator::setCompressRatio(double value)
	{
		bool isValueValid = value > 0. && value < 100.;
		imgCompressRatio = isValueValid ? value : -1.;
	}

	// crp - compress ratio percent
	cv::Mat Detectorator::resizeImg(cv::Mat img, double crp)
	{
		cv::Mat scaledImg;
		double scaleValue {crp / 100.};
		int width {(int)(img.cols * scaleValue)};
		int height {(int)(img.rows * scaleValue)};
		cv::resize(img, scaledImg, cv::Size(width, height), cv::INTER_LINEAR);
		return scaledImg;
	}
}
