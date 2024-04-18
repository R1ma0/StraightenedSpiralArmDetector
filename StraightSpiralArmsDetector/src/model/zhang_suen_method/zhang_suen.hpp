#ifndef ZHANG_SUEN_HPP
#define ZHANG_SUEN_HPP

#include <opencv2/opencv.hpp>
#include <vector>

typedef std::vector<int> vInt;
typedef std::vector<cv::Point> vPoint;

const vInt STEP_ONE_NEIGHBOURS_IDX{ 0, 2, 6, 0, 4, 6 };
const vInt STEP_TWO_NEIGHBOURS_IDX{ 0, 2, 4, 2, 4, 6 };

class ZhangSuen
{
private:
	void extractSumOfTransitions(int&, vInt);
	void processPixels(cv::Mat&, bool&, vInt, vInt);
public:
	cv::Mat execute(cv::Mat, bool);
	cv::Mat resizeImage(cv::Mat, double);
	cv::Mat replacePixelValue(cv::Mat, uchar, uchar);
	int getSumOfVector(vInt);
	int getSumOfVectorExclude(vInt, vInt&);
	int getSumOfVectorInclude(vInt, vInt&);
	void extractPixelNeighbours(cv::Mat&, int, int, vInt&);
};

#endif
