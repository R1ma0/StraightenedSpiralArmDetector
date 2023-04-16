#ifndef DETECTORATOR_H
#define DETECTORATOR_H

#include <iostream>
#include <opencv2/opencv.hpp>

namespace detectorator_namespace
{
	class Detectorator
	{
	public:
		cv::Mat execute(cv::Mat);
	private:
		cv::Mat resizeImg(cv::Mat img, double crp);
	};
}

#endif
