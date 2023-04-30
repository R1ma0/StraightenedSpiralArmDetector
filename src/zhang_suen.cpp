#include "zhang_suen.h"

namespace zhang_suen_namespace
{
	void ZhangSuen::execute(cv::Mat & inImg)
	{
		unsigned int neighboursSize {8};
		int * neighbours {new int[neighboursSize]};
		bool isStepOneChangesComplete {false};
		bool isStepTwoChangesComplete {false};
		std::vector<int> stepOneNeighboursIdx {0, 2, 6, 0, 4, 6};
		std::vector<int> stepTwoNeighboursIdx {0, 2, 4, 2, 4, 6};

		replacePixelValue(inImg, 255, 1);

		while (!isStepOneChangesComplete || !isStepTwoChangesComplete)
		{
			processPixels(
				inImg, isStepOneChangesComplete, stepOneNeighboursIdx, neighbours, 
				neighboursSize
			);
			processPixels(
				inImg, isStepTwoChangesComplete, stepTwoNeighboursIdx, neighbours,
				neighboursSize
			);
		}

		delete [] neighbours;
		neighbours = nullptr;
		
		replacePixelValue(inImg, 1, 255);
	}

	void ZhangSuen::processPixels(
		cv::Mat & img, bool & isComplete, std::vector<int> & nIdx, int * neighbours,
		unsigned int neighboursSize
	)
	{
		int sumOfTransitions;
		int sumOfNeighbours;
		bool isFirstConditionMet;
		bool isSecondConditionMet;
		bool isThirdConditionMet;
		bool isFourthConditionMet;
		bool isFifthConditionMet;
		bool isSixthConditionMet;
		bool isAllConditionsMet;
		std::vector<cv::Point> stepChanges;

		for (int r = 1; r < img.rows - 1; r++)
		{
			for (int c = 1; c < img.cols - 1; c++)
			{
				extractPixelNeighbours(img, r, c, neighbours);
				extractSumOfTransitions(sumOfTransitions, neighbours, neighboursSize);
				sumOfNeighbours = getSumOfNeighbours(neighbours, neighboursSize);

				isFirstConditionMet = img.at<uchar>(r, c) == 1;
				isSecondConditionMet = sumOfNeighbours >= 2;
				isThirdConditionMet = sumOfNeighbours <= 6;
				isFourthConditionMet = sumOfTransitions == 1;
				isFifthConditionMet = neighbours[nIdx[0]] * 
									  neighbours[nIdx[1]] * 
									  neighbours[nIdx[2]] == 0;
				isSixthConditionMet = neighbours[nIdx[3]] * 
									  neighbours[nIdx[4]] *
									  neighbours[nIdx[5]] == 0;
				isAllConditionsMet = isFirstConditionMet && isSecondConditionMet && 
									 isThirdConditionMet && isFourthConditionMet &&
									 isFifthConditionMet && isSixthConditionMet;

				if (isAllConditionsMet)
				{
					stepChanges.push_back(cv::Point(r, c));
				}
			}
		}

		if (stepChanges.empty())
		{
			isComplete = true;
		}
		else
		{
			for (cv::Point p : stepChanges)
			{
				img.at<uchar>(p.x, p.y) = 0;
			}
		}
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
