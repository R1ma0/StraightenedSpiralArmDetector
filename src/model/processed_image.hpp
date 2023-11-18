#ifndef PROCESSED_IMAGE_H
#define PROCESSED_IMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>

class ProcessedImage
{
private:
    cv::Mat image;
    double rotationAngleDegrees = 0.0;
public:
    cv::Mat GetProcessedImage();
    double GetRotationAngleDegrees();
    bool LoadImage(const std::string);
    bool SaveImage(const std::string);
    cv::Mat RotateImage(cv::Mat, double);
};

#endif
