#ifndef ADAPTIVE_ZHANG_SUEN_HPP
#define ADAPTIVE_ZHANG_SUEN_HPP

#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include "zhang_suen.hpp"

typedef unsigned int uint;

enum class PixelsOperation { Add, Remove };

struct AdaptiveZhangSuenParameters
{
    float binaryThreshValue;
    float gaussConst;
    float imgCompressPercentage;
    int gaussBlockSize; // Size of a pixel neighbourhood : 3, 5, 7, ...
};

struct AZSParametersRanges
{
    AdaptiveZhangSuenParameters min;
    AdaptiveZhangSuenParameters max;
    AdaptiveZhangSuenParameters step;
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
    ZhangSuen* zhangSuen;
    PixelPatterns* patternsToRemove;
    PixelPatterns* patternsToAdd;
    bool isPixelMatchesPatterns(vInt&, PixelPatterns*);
    void performAnOperationWithPixels(PixelsOperation, cv::Mat);
public:
    AdaptiveZhangSuenMethod();
    ~AdaptiveZhangSuenMethod();
    cv::Mat execute(cv::Mat, AdaptiveZhangSuenParameters);
};

#endif
