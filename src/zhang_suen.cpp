#include "zhang_suen.h"

namespace zhang_suen_namespace
{
	void ZhangSuen::execute(cv::Mat & inImg)
	{
		int * neighbours {new int[8]};
		int sumOfTransitions;
		
		replacePixelValue(inImg, 255, 1);
		//extractPixelNeighbours(inImg, 1, 1, neighbours);
		//extractSumOfTransitions(sumOfTransitions, neighbours);
		replacePixelValue(inImg, 1, 255);
		
		delete [] neighbours;
		neighbours = nullptr;
	}

	void ZhangSuen::replacePixelValue(cv::Mat & inImg, uchar from, uchar to)
	{
		for (int r = 0; r < inImg.rows; r++)
		{
			for (int c = 0; c < inImg.cols; c++)
			{
				uchar & pixel = inImg.at<uchar>(r, c);
				if (pixel == from) pixel = to;
			}
		}
	}

	void ZhangSuen::extractSumOfTransitions(int & sum, int * n)
	{
		sum = 0;

		for (int i = 0; i < 7; i++)
		{
			sum += (n[i] == 0 && n[i + 1] == 1) ? 1 : 0;
		}

		sum += (n[7] == 0 && n[0] == 1) ? 1 : 0;
	}

	void ZhangSuen::extractPixelNeighbours(cv::Mat & img, int r, int c, int * n)
	{
		n[0] = int(img.at<uchar>(r - 1, c    ));
		n[1] = int(img.at<uchar>(r - 1, c + 1));
		n[2] = int(img.at<uchar>(r    , c + 1));
		n[3] = int(img.at<uchar>(r + 1, c + 1));
		n[4] = int(img.at<uchar>(r + 1, c    ));
		n[5] = int(img.at<uchar>(r + 1, c - 1));
		n[6] = int(img.at<uchar>(r    , c - 1));
		n[7] = int(img.at<uchar>(r - 1, c - 1));
	}
}
