#ifndef ADAPTIVE_ZHANG_SUEN_HPP
#define ADAPTIVE_ZHANG_SUEN_HPP

#include <opencv2/opencv.hpp>
#include "zhang_suen.hpp"
#include "utils.hpp"
#include "adaptive_zhang_suen_types.hpp"

class AdaptiveZhangSuenMethod
{
private:
    Utils* utils;
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
