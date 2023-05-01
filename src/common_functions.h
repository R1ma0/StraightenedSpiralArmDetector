#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTION_H

#include <opencv2/opencv.hpp>
#include <vector>

namespace common_functions_namespace
{
	class CommonFunctions
	{
	public:
		int getSumOfNeighbours(std::vector<int>, std::vector<int>);
		int getSumOfNeighbours(std::vector<int>);
		void extractPixelNeighbours(cv::Mat &, int, int, std::vector<int> &);
	};
}

#endif
