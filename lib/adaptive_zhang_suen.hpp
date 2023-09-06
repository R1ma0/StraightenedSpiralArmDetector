#ifndef ADAPTIVE_ZHANG_SUEN_HPP
#define ADAPTIVE_ZHANG_SUEN_HPP

#include <opencv2/opencv.hpp>
#include <cstdlib>
#include "zhang_suen.hpp"
#include "utils.hpp"

enum class PixelsOperation {Add, Remove};

struct AdaptiveZhangSuenParameters
{
    float binaryThreshValue;
    float gaussConst;
    float imgCompressPercentage;
    int gaussBlockSize; // Size of a pixel neighbourhood : 3, 5, 7, ...
};

struct PixelPatterns
{
	std::vector<vInt> composite;
	vInt compositeSum;
	vInt simple;
};

class AdaptiveZhangSuenMethod
{
private:
    Utils *utils;
    ZhangSuen *zhangSuen;
    PixelPatterns *patternsToRemove;
    PixelPatterns *patternsToAdd;
    bool isPixelMatchesPatterns(vInt &, PixelPatterns *);
	void performAnOperationWithPixels(PixelsOperation, cv::Mat);
public:
    AdaptiveZhangSuenMethod();
    ~AdaptiveZhangSuenMethod();
    cv::Mat execute(cv::Mat, AdaptiveZhangSuenParameters);
};

#endif // ADAPTIVE_ZHANG_SUEN_HPP
