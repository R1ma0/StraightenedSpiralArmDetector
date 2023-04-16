#ifndef DETECTORATOR_UTILS_H
#define DETECTORATOR_UTILS_H

#include <opencv2/opencv.hpp>

namespace detectorator_utils_namespace
{
	class DetectoratorUtils
	{
	public:
		cv::Mat resizeImage(cv::Mat image, int scalePercent);
	};
}

#endif
