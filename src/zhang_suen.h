#ifndef ZHANG_SUEN_H
#define ZHANG_SUEN_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "common_functions.h"
#include "aliases.h"

namespace cf = common_functions_namespace;

namespace zhang_suen_namespace
{
	class ZhangSuen
	{
	private:
		void extractSumOfTransitions(int &, vInt);
		void processPixels(cv::Mat &, bool &, vInt &, vInt);
	public:
		void replacePixelValue(cv::Mat &, uchar, uchar);
		void execute(cv::Mat &, bool);
	};
}

#endif
