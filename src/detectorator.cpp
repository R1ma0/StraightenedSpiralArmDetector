#include "detectorator.h"

namespace detectorator_namespace
{
	cv::Mat Detectorator::execute(cv::Mat image)
	{
		return resizeImg(image, 20.);
	}

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
