/* \file
 * \brief Contains the implementation of core
 *        functions for string displaying
 */
#include "detectorator.h"

namespace detectorator_namespace
{
	/* \brief Performs operations to highlight strings
	 */
	void Detectorator::execute(cv::Mat inImg, cv::Mat &outImg)
	{
		cv::adaptiveThreshold(
			inImg,
			outImg, 
			255.,
			cv::ADAPTIVE_THRESH_GAUSSIAN_C, 
			cv::THRESH_BINARY,
			gaussBlockSize,
			gaussConst
		);
		resizeImg(outImg, imgCompressPercentage);
		cv::threshold(
			outImg, 
			outImg, 
			binaryThreshValue, 
			255., 
			cv::THRESH_BINARY
		);
		zs::ZhangSuen zhangSuen;
		zhangSuen.replacePixelValue(outImg, 255, 1);
		performAnOperationWithPixels(PixelsOperation::Add, outImg);
		performAnOperationWithPixels(PixelsOperation::Remove, outImg);
		zhangSuen.execute(outImg, false);
		zhangSuen.replacePixelValue(outImg, 1, 255);
	}

	/* In this function is used cv::INTER_LINEAR method
	 *
	 * \param img Image for resizing
	 * \param cp Image compression power
	 * \return Reduced image
	 */
	void Detectorator::resizeImg(cv::Mat &outImg, double cp)
	{
		double scaleValue {cp / 100.};
		int width {(int)(outImg.cols * scaleValue)};
		int height {(int)(outImg.rows * scaleValue)};
		
		cv::resize(outImg, outImg, cv::Size(width, height), cv::INTER_LINEAR);
	}

	void Detectorator::readImg(fs::path from, cv::Mat &to)
	{
		to = cv::imread(from, cv::IMREAD_GRAYSCALE);
		
		if (to.empty())
		{
			reportFailedOperation(
				"Could not read the image : " + std::string(from), true
			);
		}
	}

	void Detectorator::writeImg(cv::Mat &from, fs::path to)
	{
		bool isImgWrite {cv::imwrite(to, from)};

		if (!isImgWrite)
		{
			reportFailedOperation(
				"The image was not saved : " + std::string(to), true
			);
		}
	}

	void Detectorator::performAnOperationWithPixels(PixelsOperation op, cv::Mat &inImg)
	{
		cf::CommonFunctions cf;
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
			for (int r = 1; r < inImg.rows - 1; r++)
			{
				for (int c = 1; c < inImg.cols - 1; c++)
				{		
					cf.extractPixelNeighbours(inImg, r, c, neighbours);

					switch (op)
					{
						case PixelsOperation::Add:
							if (inImg.at<uchar>(r, c) == 0)
							{
								if (isPixelMatchesPatterns(neighbours, patternsToAdd, cf))
								{
									pixelsToChange.push_back(cv::Point(r, c));
								}
							}
							break;
						case PixelsOperation::Remove:
							if (inImg.at<uchar>(r, c) == 1)
							{
								if (isPixelMatchesPatterns(neighbours, patternsToRemove, cf))
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
					inImg.at<uchar>(pixel.x, pixel.y) = (op == PixelsOperation::Remove) ? 0 : 1;
				}

				pixelsToChange.clear();
			}
		}
	}

	bool Detectorator::isPixelMatchesPatterns(
		vInt &n, PixelPatterns &patterns, cf::CommonFunctions &cf
	)
	{
		bool statementOne;
		bool statementTwo;

		for (auto spv : patterns.simple)
		{
			if (cf.getSumOfVector(n) == spv) return true;
		}

		for (int idx = 0; idx < patterns.composite.size(); idx++)
		{
			statementOne = cf.getSumOfVectorExclude(
				n, patterns.composite[idx]
			) == patterns.compositeSum[idx];
			statementTwo = cf.getSumOfVectorInclude(n, patterns.composite[idx]) == 0;

			if (statementOne && statementTwo) return true;
		}

		return false;
	}

	void Detectorator::setImgCompressPercentage(double value)
	{
		if (value <= 0. || value > 100.)
		{
			reportFailedOperation(
				"Compression value out of range ( 0. < value <= 100. )", true
			);
		}

		imgCompressPercentage = value;
	}

	void Detectorator::setThreshBinValue(double value)
	{
		if (value < 0. || value > 255.)
		{
			reportFailedOperation(
				"Threshold binarization value out of range (0. <= value <= 255.)", true
			);
		}

		threshBinValue = value;
	}

	void Detectorator::reportFailedOperation(std::string msg, bool close)
	{
		std::cout << "FAILDED. " + msg << std::endl;
		if (close)
			exit(0);
	}

	void Detectorator::setBinaryThreshValue(double value)
	{
		if (value < 0. || value > 255.)
		{
			reportFailedOperation(
				"Binary threshold value out of range (0. <= value <= 255.)", true
			);
		}

		binaryThreshValue = value;
	}
}
