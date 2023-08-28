#ifndef ZHANG_SUEN_H
#define ZHANG_SUEN_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "common_functions.hpp"
#include "aliases.hpp"

const vInt STEP_ONE_NEIGHBOURS_IDX {0, 2, 6, 0, 4, 6};
const vInt STEP_TWO_NEIGHBOURS_IDX {0, 2, 4, 2, 4, 6};

class ZhangSuen
{
private:
	void extractSumOfTransitions(int &, vInt);
	void processPixels(cv::Mat &, bool &, vInt, vInt);
public:
	void replacePixelValue(cv::Mat &, uchar, uchar);
	void execute(cv::Mat &, bool);
};

#endif
