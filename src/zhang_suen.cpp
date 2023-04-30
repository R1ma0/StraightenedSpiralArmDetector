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
		bool isFirstConditionMet;
		bool isSecondConditionMet;
		bool isThirdConditionMet;
		bool isFourthConditionMet;
		bool isFifthConditionMet;
		bool isSixthConditionMet;
		bool isAllConditionsMet;
		std::vector<cv::Point> stepOneChanges;
		std::vector<cv::Point> stepTwoChanges;
	
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

					isFirstConditionMet = inImg.at<uchar>(r, c) == 1;
					isSecondConditionMet = sumOfNeighbours >= 2;
					isThirdConditionMet = sumOfNeighbours <= 6;
					isFourthConditionMet = sumOfTransitions == 1;
					isFifthConditionMet = neighbours[0] * neighbours[2] * neighbours[4] == 0;
					isSixthConditionMet = neighbours[2] * neighbours[4] * neighbours[6] == 0;
					isAllConditionsMet = isFirstConditionMet && isSecondConditionMet && 
										 isThirdConditionMet && isFourthConditionMet &&
										 isFifthConditionMet && isSixthConditionMet;

					if (isAllConditionsMet)
					{
						stepOneChanges.push_back(cv::Point(r, c));
					}
				}
			}

			if (stepOneChanges.empty())
			{
				isStepOneChangesComplete = true;
			}
			else
			{
				for (cv::Point p : stepOneChanges)
				{
					inImg.at<uchar>(p.x, p.y) = 0;
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

					isFirstConditionMet = inImg.at<uchar>(r, c) == 1;
					isSecondConditionMet = sumOfNeighbours >= 2;
					isThirdConditionMet = sumOfNeighbours <= 6;
					isFourthConditionMet = sumOfTransitions == 1;
					isFifthConditionMet = neighbours[0] * neighbours[2] * neighbours[6] == 0;
					isSixthConditionMet = neighbours[0] * neighbours[4] * neighbours[6] == 0;
					isAllConditionsMet = isFirstConditionMet && isSecondConditionMet && 
										 isThirdConditionMet && isFourthConditionMet &&
										 isFifthConditionMet && isSixthConditionMet;

					if (isAllConditionsMet)
					{
						stepTwoChanges.push_back(cv::Point(r, c));
					}
				}
			}

			if (stepTwoChanges.empty())
			{
				isStepTwoChangesComplete = true;
			}
			else
			{
				for (cv::Point p : stepTwoChanges)
				{
					inImg.at<uchar>(p.x, p.y) = 0;
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
