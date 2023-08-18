#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "aliases.h"

namespace common_functions_namespace
{
	class CommonFunctions
	{
	public:
		int getSumOfVector(vInt);
		int getSumOfVectorExclude(vInt, vInt &);
		int getSumOfVectorInclude(vInt, vInt &);
		void extractPixelNeighbours(cv::Mat &, int, int, vInt &);
	};
}

#endif
