#include "utils.hpp"

cv::Mat Utils::resizeImage(cv::Mat img, double cp)
{
	double scaleValue {cp / 100.};
	int width {(int)(img.cols * scaleValue)};
	int height {(int)(img.rows * scaleValue)};
	
	cv::resize(img, img, cv::Size(width, height), cv::INTER_LINEAR);

    return img;
}

cv::Mat Utils::replacePixelValue(cv::Mat img, uchar from, uchar to)
{
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			uchar & pixel = img.at<uchar>(r, c);
			if (pixel == from) pixel = to;
		}
	}
	
	return img;
}

int Utils::getSumOfVector(vInt n)
{
	int sum = 0;

	for (int value : n)
	{
		sum += value;
	}

	return sum;
}

int Utils::getSumOfVectorExclude(vInt n, vInt &exclude)
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

int Utils::getSumOfVectorInclude(vInt n, vInt &include)
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

void Utils::extractPixelNeighbours(cv::Mat &img, int r, int c, vInt &n)
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
