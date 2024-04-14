#include "zhang_suen.hpp"

ZhangSuen::ZhangSuen()
{
    utils = new Utils();
}

ZhangSuen::~ZhangSuen()
{
    free(utils);
}

cv::Mat ZhangSuen::execute(cv::Mat img, bool replace)
{
	bool isStepOneChangesComplete{ false };
	bool isStepTwoChangesComplete{ false };
	vInt neighbours(8);

	if (replace)
		img = utils->replacePixelValue(img, 255, 1);

	while (!isStepOneChangesComplete || !isStepTwoChangesComplete)
	{
		processPixels(
			img, isStepOneChangesComplete, STEP_ONE_NEIGHBOURS_IDX, neighbours
		);
		processPixels(
			img, isStepTwoChangesComplete, STEP_TWO_NEIGHBOURS_IDX, neighbours
		);
	}
	
	if (replace)
		img = utils->replacePixelValue(img, 1, 255);
		
	return img;
}

void ZhangSuen::processPixels(
	cv::Mat& img, bool& isComplete, vInt nIdx, vInt neighbours
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
	vPoint stepChanges;

	for (int r = 1; r < img.rows - 1; r++)
	{
		for (int c = 1; c < img.cols - 1; c++)
		{
			utils->extractPixelNeighbours(img, r, c, neighbours);
			extractSumOfTransitions(sumOfTransitions, neighbours);
			sumOfNeighbours = utils->getSumOfVector(neighbours);

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

			if (isAllConditionsMet) stepChanges.push_back(cv::Point(r, c));
		}
	}

	if (stepChanges.empty()) isComplete = true;
	else
	{
		for (cv::Point p : stepChanges)
		{
			img.at<uchar>(p.x, p.y) = 0;
		}
	}
}

void ZhangSuen::extractSumOfTransitions(int& sum, vInt n)
{
	sum = 0;

	for (long unsigned int i = 0; i < n.size() - 1; i++)
	{
		sum += (n[i] == 0 && n[i + 1] == 1) ? 1 : 0;
	}

	sum += (n[n.size() - 1] == 0 && n[0] == 1) ? 1 : 0;
}
