// Implementation of the method of skeletonization of Zhang Suen

#ifndef ZHANG_SUEN_HPP
#define ZHANG_SUEN_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include "utils.hpp"

const vInt STEP_ONE_NEIGHBOURS_IDX {0, 2, 6, 0, 4, 6};
const vInt STEP_TWO_NEIGHBOURS_IDX {0, 2, 4, 2, 4, 6};

class ZhangSuen
{
private:
    Utils *utils;
	void extractSumOfTransitions(int &, vInt);
	void processPixels(cv::Mat &, bool &, vInt, vInt);
public:
    ZhangSuen();
    ~ZhangSuen();
	cv::Mat execute(cv::Mat, bool);
};

#endif
