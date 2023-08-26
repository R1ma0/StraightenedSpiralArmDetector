#ifndef DETECTORATOR_H
#define DETECTORATOR_H

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <cstdlib>
#include <string>
#include "zhang_suen.h"
#include "aliases.h"

namespace fs = std::filesystem;

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
	cv::Mat img;
	void resizeImg(double);
	void reportFailedOperation(std::string, bool);
	void performAnOperationWithPixels(PixelsOperation);
	float binaryThreshValue;
	float gaussConst; /// Constant subtracted from the mean of weighted mean
	float imgCompressPercentage;
	int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
	bool isPixelMatchesPatterns(vInt &, PixelPatterns &, CommonFunctions &);
public:
	void execute();
	void readImg(fs::path);
	void writeImg(fs::path);
	void setBinaryThreshValue(float value) { binaryThreshValue = value; };
	void setImgCompressPercentage(float value) { imgCompressPercentage = value; };
	void setGaussConst(float value) { gaussConst = value; };
	void setGaussBlockSize(int value) { gaussBlockSize = value; };
};

#endif
