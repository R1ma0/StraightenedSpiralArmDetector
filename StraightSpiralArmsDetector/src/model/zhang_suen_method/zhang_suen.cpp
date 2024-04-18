#include "zhang_suen.hpp"

cv::Mat ZhangSuen::execute(cv::Mat img, bool replace)
{
	bool isStepOneChangesComplete{ false };
	bool isStepTwoChangesComplete{ false };
	vInt neighbours(8);

	if (replace)
		img = replacePixelValue(img, 255, 1);

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
		img = replacePixelValue(img, 1, 255);
		
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
			extractPixelNeighbours(img, r, c, neighbours);
			extractSumOfTransitions(sumOfTransitions, neighbours);
			sumOfNeighbours = getSumOfVector(neighbours);

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

cv::Mat ZhangSuen::resizeImage(cv::Mat img, double cp)
{
	double scaleValue{ cp / 100. };
	int width{ (int)(img.cols * scaleValue) };
	int height{ (int)(img.rows * scaleValue) };

	cv::resize(img, img, cv::Size(width, height), cv::INTER_LINEAR);

	return img;
}

cv::Mat ZhangSuen::replacePixelValue(cv::Mat img, uchar from, uchar to)
{
	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; c++)
		{
			uchar& pixel = img.at<uchar>(r, c);
			if (pixel == from) pixel = to;
		}
	}

	return img;
}

int ZhangSuen::getSumOfVector(vInt n)
{
	int sum = 0;

	for (int value : n)
	{
		sum += value;
	}

	return sum;
}

int ZhangSuen::getSumOfVectorExclude(vInt n, vInt& exclude)
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

int ZhangSuen::getSumOfVectorInclude(vInt n, vInt& include)
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

void ZhangSuen::extractPixelNeighbours(cv::Mat& img, int r, int c, vInt& n)
{
	n[0] = img.at<uchar>(r - 1, c);
	n[1] = img.at<uchar>(r - 1, c + 1);
	n[2] = img.at<uchar>(r, c + 1);
	n[3] = img.at<uchar>(r + 1, c + 1);
	n[4] = img.at<uchar>(r + 1, c);
	n[5] = img.at<uchar>(r + 1, c - 1);
	n[6] = img.at<uchar>(r, c - 1);
	n[7] = img.at<uchar>(r - 1, c - 1);
}
