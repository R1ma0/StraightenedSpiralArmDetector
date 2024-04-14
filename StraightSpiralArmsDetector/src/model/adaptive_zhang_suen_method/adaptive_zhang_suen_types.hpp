#ifndef ADAPTIVE_ZHANG_SUEN_TYPES_H
#define ADAPTIVE_ZHANG_SUEN_TYPES_H

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <vector>

typedef std::vector<int> vInt;
typedef std::vector<cv::Point> vPoint;
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

#endif