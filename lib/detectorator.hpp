#ifndef DETECTORATOR_HPP
#define DETECTORATOR_HPP

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <string>
#include "zhangSuen.hpp"
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
	cv::Mat img;
	void resizeImg(double);
	void performAnOperationWithPixels(PixelsOperation);
	float binaryThreshValue;
	float gaussConst; /// Constant subtracted from the mean of weighted mean
	float imgCompressPercentage;
	int gaussBlockSize; /// Size of a pixel neighbourhood : 3, 5, 7, ...
	bool isPixelMatchesPatterns(vInt &, PixelPatterns &, Utils &);
public:
	void execute();
    void setImage(cv::Mat);
    cv::Mat getImage();
	void setBinaryThreshValue(float value) { binaryThreshValue = value; };
	void setImgCompressPercentage(float value) { imgCompressPercentage = value; };
	void setGaussConst(float value) { gaussConst = value; };
	void setGaussBlockSize(int value) { gaussBlockSize = value; };
};

#endif
