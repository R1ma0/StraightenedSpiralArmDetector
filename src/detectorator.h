#ifndef DETECTORATOR_H
#define DETECTORATOR_H

#include <iostream>
#include <opencv2/opencv.hpp>

namespace detectorator_namespace
{
	class Detectorator
	{
	private:
		double imgCompressRatio;
		cv::Mat resizeImg(cv::Mat img, double crp);
	public:
		cv::Mat execute(cv::Mat);
		void setCompressRatio(double value);
	};
}

#endif
