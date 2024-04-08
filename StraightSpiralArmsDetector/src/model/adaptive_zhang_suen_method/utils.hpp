#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include "adaptive_zhang_suen_types.hpp"

class Utils
{
public:
	cv::Mat resizeImage(cv::Mat, double);
	cv::Mat replacePixelValue(cv::Mat, uchar, uchar);
	int getSumOfVector(vInt);
	int getSumOfVectorExclude(vInt, vInt&);
	int getSumOfVectorInclude(vInt, vInt&);
	void extractPixelNeighbours(cv::Mat&, int, int, vInt&);
};

#endif
