#include "detectorator.hpp"

void Detectorator::execute()
{
	cv::adaptiveThreshold(
		this->img,
		this->img, 
		255.,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
		cv::THRESH_BINARY,
		this->gaussBlockSize,
		this->gaussConst
	);
	resizeImg(this->imgCompressPercentage);
	cv::threshold(
		this->img, 
		this->img, 
		this->binaryThreshValue, 
		255., 
		cv::THRESH_BINARY
	);
	ZhangSuen zhangSuen;
	zhangSuen.replacePixelValue(this->img, 255, 1);
	performAnOperationWithPixels(PixelsOperation::Add);
	performAnOperationWithPixels(PixelsOperation::Remove);
	zhangSuen.execute(this->img, false);
	zhangSuen.replacePixelValue(this->img, 1, 255);
}

void Detectorator::setImage(cv::Mat image)
{
    this->img = image;
}

cv::Mat Detectorator::getImage()
{
    return this->img;
}

void Detectorator::resizeImg(double cp)
{
	double scaleValue {cp / 100.};
	int width {(int)(this->img.cols * scaleValue)};
	int height {(int)(this->img.rows * scaleValue)};
	
	cv::resize(this->img, this->img, cv::Size(width, height), cv::INTER_LINEAR);
}

void Detectorator::performAnOperationWithPixels(PixelsOperation op)
{
	Utils utils;
	vPoint pixelsToChange;
	vInt neighbours (8);
	bool isNotAllPixelsChanged = true;

	PixelPatterns patternsToRemove;
	patternsToRemove.composite = {
		{2, 6},	{0, 4}, {7, 0, 1}, {7, 6, 5}, {3, 4, 5}, {1, 2, 3}, {1, 3, 5, 7},
		{7, 0, 1, 3, 5}, {7, 6, 1, 3, 5}, {7, 1, 3, 4, 5}, {1, 2, 3, 5, 7}
	};
	patternsToRemove.compositeSum = {6, 6, 3, 3, 3, 3, 4, 5, 5, 5, 5};
	patternsToRemove.simple = {0};

	PixelPatterns patternsToAdd;
	patternsToAdd.composite = {
		{1, 3, 5, 7}, {0, 1, 7}, {3, 4, 5}, {5, 6, 7}, {1, 2, 3}, {3, 7}, 
		{1, 5}, {0, 7}, {4, 5}, {0, 1}, {3, 4}, {3, 5, 7}, {1, 3, 5}, 
		{1, 3, 7}, {1, 5, 7}
	};
	patternsToAdd.compositeSum = {4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5};
	patternsToAdd.simple = {8, 7};

	while (isNotAllPixelsChanged)
	{
		for (int r = 1; r < this->img.rows - 1; r++)
		{
			for (int c = 1; c < this->img.cols - 1; c++)
			{		
				utils.extractPixelNeighbours(this->img, r, c, neighbours);

				switch (op)
				{
					case PixelsOperation::Add:
						if (this->img.at<uchar>(r, c) == 0)
						{
							if (isPixelMatchesPatterns(neighbours, patternsToAdd, utils))
							{
								pixelsToChange.push_back(cv::Point(r, c));
							}
						}
						break;
					case PixelsOperation::Remove:
						if (this->img.at<uchar>(r, c) == 1)
						{
							if (isPixelMatchesPatterns(neighbours, patternsToRemove, utils))
							{
								pixelsToChange.push_back(cv::Point(r, c));
							}
						}
						break;
				}
			}
		}

		if (pixelsToChange.empty()) isNotAllPixelsChanged = false;
		else
		{
			for (cv::Point pixel: pixelsToChange)
			{
				this->img.at<uchar>(pixel.x, pixel.y) = (op == PixelsOperation::Remove) ? 0 : 1;
			}

			pixelsToChange.clear();
		}
	}
}

bool Detectorator::isPixelMatchesPatterns(
	vInt &n, PixelPatterns &patterns, Utils &utils
)
{
	bool statementOne;
	bool statementTwo;

	for (auto spv : patterns.simple)
	{
		if (utils.getSumOfVector(n) == spv) return true;
	}

	for (int idx = 0; idx < patterns.composite.size(); idx++)
	{
		statementOne = utils.getSumOfVectorExclude(
			n, patterns.composite[idx]
		) == patterns.compositeSum[idx];
		statementTwo = utils.getSumOfVectorInclude(n, patterns.composite[idx]) == 0;

		if (statementOne && statementTwo) return true;
	}

	return false;
}
