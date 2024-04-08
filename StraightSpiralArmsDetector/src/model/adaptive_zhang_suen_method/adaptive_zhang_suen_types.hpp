#ifndef ADAPTIVE_ZHANG_SUEN_TYPES_H
#define ADAPTIVE_ZHANG_SUEN_TYPES_H

#include <cstdlib>

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

struct PixelPatterns
{
    std::vector<vInt> composite;
    vInt compositeSum;
    vInt simple;
};

#endif