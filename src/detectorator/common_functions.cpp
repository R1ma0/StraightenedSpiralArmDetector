#include "common_functions.h"

int CommonFunctions::getSumOfVector(vInt n)
{
	int sum = 0;

	for (int value : n)
	{
		sum += value;
	}

	return sum;
}

int CommonFunctions::getSumOfVectorExclude(vInt n, vInt &exclude)
{
	int sum = 0;

	if (!exclude.empty())
	{
		for (auto item : exclude)
		{
			n[item] = 0;
		}
	}

	for (auto value : n)
	{
		sum += value;
	}

	return sum;
}

int CommonFunctions::getSumOfVectorInclude(vInt n, vInt &include)
{
	int sum = 0;

	if (!include.empty())
	{
		for (auto value : include)
		{
			sum += n[value];
		}
	}

	return sum;
}

void CommonFunctions::extractPixelNeighbours(cv::Mat &img, int r, int c, vInt &n)
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