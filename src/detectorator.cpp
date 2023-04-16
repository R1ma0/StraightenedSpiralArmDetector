#include "detectorator.h"

namespace detectorator_namespace
{
	cv::Mat Detectorator::execute(cv::Mat image)
	{
		dsgu::DetectoratorUtils d_utils;
		return d_utils.resizeImage(image, 20);
	}
}
