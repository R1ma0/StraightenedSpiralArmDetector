#ifndef ZHANG_SUEN_H
#define ZHANG_SUEN_H

#include <opencv2/opencv.hpp>

namespace zhang_suen_namespace
{
	class ZhangSuen
	{
	private:
		void replacePixelValue(cv::Mat &, uchar, uchar);
		void extractSumOfTransitions(int &, int *);
		void extractPixelNeighbours(cv::Mat &, int, int, int *);
	public:
		void execute(cv::Mat &);
	};
}

#endif
