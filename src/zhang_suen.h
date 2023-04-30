#ifndef ZHANG_SUEN_H
#define ZHANG_SUEN_H

#include <opencv2/opencv.hpp>
#include <vector>

namespace zhang_suen_namespace
{
	class ZhangSuen
	{
	private:
		int getSumOfNeighbours(int *, int);
		void replacePixelValue(cv::Mat &, uchar, uchar);
		void extractSumOfTransitions(int &, int *, int);
		void extractPixelNeighbours(cv::Mat &, int, int, int *);
		void processPixels(cv::Mat &, bool &, std::vector<int> &, int *, unsigned int);
	public:
		void execute(cv::Mat &);
	};
}

#endif
