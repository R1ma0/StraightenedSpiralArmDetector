#include "zhang_suen.h"

namespace zhang_suen_namespace
{
	void ZhangSuen::execute(cv::Mat & inImg)
	{
		unsigned int neighboursSize {8};
		int * neighbours {new int[neighboursSize]};
		int sumOfTransitions;
		int sumOfNeighbours;
		bool isStepOneChangesComplete {false};
		bool isStepTwoChangesComplete {false};
		std::forward_list<cv::Point2i> stepOneChanges;
		std::forward_list<cv::Point2i> stepTwoChanges;
		
		replacePixelValue(inImg, 255, 1);

		while (!isStepOneChangesComplete || !isStepTwoChangesComplete)
		{
			stepOneChanges.clear();
			stepTwoChanges.clear();

			// Step one
			for (int r = 1; r < inImg.rows - 1; r++)
			{
				for (int c = 1; c < inImg.cols - 1; c++)
				{
					extractPixelNeighbours(inImg, r, c, neighbours);
					extractSumOfTransitions(sumOfTransitions, neighbours, neighboursSize);
					sumOfNeighbours = getSumOfNeighbours(neighbours, neighboursSize);
					
					if (
						inImg.at<uchar>(r, c) == 1 &&
						sumOfNeighbours >= 2 && 
						sumOfNeighbours <= 6 &&
						sumOfTransitions == 1 &&
						neighbours[0] * neighbours[2] * neighbours[4] == 0 &&
						neighbours[2] * neighbours[4] * neighbours[6] == 0
					)
					{
						stepOneChanges.insert_after(stepOneChanges.end(), cv::Point2i(r, c));
					}
				}
			}

			if (stepOneChanges.empty())
			{
				isStepOneChangesComplete = true;
			}
			else
			{
				for (cv::Point2i p : stepOneChanges)
				{
					inImg.at<uchar>(p) = 0;
				}
			}

			// Step two
			for (int r = 1; r < inImg.rows - 1; r++)
			{
				for (int c = 1; c < inImg.cols - 1; c++)
				{
					extractPixelNeighbours(inImg, r, c, neighbours);
					extractSumOfTransitions(sumOfTransitions, neighbours, neighboursSize);
					sumOfNeighbours = getSumOfNeighbours(neighbours, neighboursSize);

					if (
						inImg.at<uchar>(r, c) == 1 &&
						sumOfNeighbours >= 2 && 
						sumOfNeighbours <= 6 &&
						sumOfTransitions == 1 &&
						neighbours[0] * neighbours[2] * neighbours[6] == 0 &&
						neighbours[0] * neighbours[4] * neighbours[6] == 0
					)
					{
						stepTwoChanges.insert_after(stepTwoChanges.end(), cv::Point2i(r, c));
					}
				}
			}

			if (stepTwoChanges.empty())
			{
				isStepTwoChangesComplete = true;
			}
			else
			{
				for (cv::Point2i p : stepTwoChanges)
				{
					inImg.at<uchar>(p) = 0;
				}
			}
		}
		
		replacePixelValue(inImg, 1, 255);
		
		delete [] neighbours;
		neighbours = nullptr;
	}

	int ZhangSuen::getSumOfNeighbours(int * n, int size)
	{
		int sum = 0;

		for (int i = 0; i < size; i++)
		{
			sum += n[i];
		}

		return sum;
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

	void ZhangSuen::extractSumOfTransitions(int & sum, int * n, int size)
	{
		sum = 0;

		for (int i = 0; i < size - 1; i++)
		{
			sum += (n[i] == 0 && n[i + 1] == 1) ? 1 : 0;
		}

		sum += (n[size - 1] == 0 && n[0] == 1) ? 1 : 0;
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
