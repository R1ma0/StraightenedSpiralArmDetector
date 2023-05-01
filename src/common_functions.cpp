#include "common_functions.h"

namespace common_functions_namespace
{
	int CommonFunctions::getSumOfNeighbours(std::vector<int> n)
	{
		int sum = 0;

		for (int value : n)
		{
			sum += value;
		}

		return sum;
	}

	int CommonFunctions::getSumOfNeighbours(std::vector<int> n, std::vector<int> exclude)
	{
		int sum = 0;

		if (!exclude.empty())
		{
			for (int item : exclude)
			{
				n[item] = 0;
			}
		}
	
		for (int value : n)
		{
			sum += value;
		}
	
		return sum;
	}
	
	void CommonFunctions::extractPixelNeighbours(cv::Mat & img, int r, int c, std::vector<int> & n)
	{
		n[0] = img.at<uchar>(r - 1, c    );
		n[1] = img.at<uchar>(r - 1, c + 1);
		n[2] = img.at<uchar>(r    , c + 1);
		n[3] = img.at<uchar>(r + 1, c + 1);
		n[4] = img.at<uchar>(r + 1, c    );
		n[5] = img.at<uchar>(r + 1, c - 1);
		n[6] = img.at<uchar>(r    , c - 1);
		n[7] = img.at<uchar>(r - 1, c - 1);
	}
}
