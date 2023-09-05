#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>

typedef std::vector<int> vInt;
typedef std::vector<cv::Point> vPoint;
typedef unsigned int uint;

class Utils
{
public:
	int getSumOfVector(vInt);
	int getSumOfVectorExclude(vInt, vInt &);
	int getSumOfVectorInclude(vInt, vInt &);
	void extractPixelNeighbours(cv::Mat &, int, int, vInt &);
};

#endif
