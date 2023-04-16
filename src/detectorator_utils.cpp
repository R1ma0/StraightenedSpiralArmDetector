#include "detectorator_utils.h"

namespace detectorator_utils_namespace
{
	cv::Mat DetectoratorUtils::resizeImage(cv::Mat image, int scalePercent)
	{
		cv::Mat scaledImage;
		double scaleValue = scalePercent / 100.;
		int width = (int)(image.cols * scaleValue); 
		int height = (int)(image.rows * scaleValue); 

		cv::resize(image, scaledImage, cv::Size(width, height), cv::INTER_LINEAR);

		return scaledImage;
	}
}
