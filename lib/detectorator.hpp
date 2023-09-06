#ifndef DETECTORATOR_HPP
#define DETECTORATOR_HPP

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <string>
#include "zhang_suen.hpp"
#include "utils.hpp"

enum class PixelsOperation {Add, Remove};

struct PixelPatterns
{
	std::vector<vInt> composite;
	vInt compositeSum;
	vInt simple;
};

class Detectorator
{
private:
    Utils *utils;
	float binaryThreshValue;
	float gaussConst; /// Constant subtracted from the mean of weighted mean
	float imgCompressPercentage;
	int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
	bool isPixelMatchesPatterns(vInt &, PixelPatterns &);
	void performAnOperationWithPixels(PixelsOperation, cv::Mat);
public:
    Detectorator();
    ~Detectorator();
    cv::Mat useAdaptiveZhangSuen(cv::Mat);
	void setBinaryThreshValue(float value) { binaryThreshValue = value; };
	void setImgCompressPercentage(float value) { imgCompressPercentage = value; };
	void setGaussConst(float value) { gaussConst = value; };
	void setGaussBlockSize(int value) { gaussBlockSize = value; };
};

#endif
