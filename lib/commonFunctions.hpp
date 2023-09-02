#ifndef COMMON_FUNCTIONS_HPP
#define COMMON_FUNCTIONS_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include "aliases.hpp"

class CommonFunctions
{
public:
	int getSumOfVector(vInt);
	int getSumOfVectorExclude(vInt, vInt &);
	int getSumOfVectorInclude(vInt, vInt &);
	void extractPixelNeighbours(cv::Mat &, int, int, vInt &);
};

#endif
