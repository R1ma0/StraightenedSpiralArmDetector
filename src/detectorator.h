#ifndef DETECTORATOR_H
#define DETECTORATOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "detectorator_utils.h"

namespace dsgu = detectorator_utils_namespace;

namespace detectorator_namespace
{
	class Detectorator
	{
	public:
		cv::Mat execute(cv::Mat);
	};
}

#endif
