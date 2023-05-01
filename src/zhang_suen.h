#ifndef ZHANG_SUEN_H
#define ZHANG_SUEN_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "common_functions.h"

namespace cf = common_functions_namespace;

namespace zhang_suen_namespace
{
	class ZhangSuen
	{
	private:
		void replacePixelValue(cv::Mat &, uchar, uchar);
		void extractSumOfTransitions(int &, std::vector<int>);
		void processPixels(cv::Mat &, bool &, std::vector<int> &, std::vector<int>);
	public:
		void execute(cv::Mat &);
	};
}

#endif
