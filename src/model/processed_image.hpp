#ifndef PROCESSED_IMAGE_H
#define PROCESSED_IMAGE_H

#include <opencv2/opencv.hpp>

class ProcessedImage
{
private:
    cv::Mat image;
    double rotationAngleDegrees = 0.0;
public:
    cv::Mat GetProcessedImage() { return image; };
    double GetRotationAngleDegrees() { return rotationAngleDegrees; }
    bool LoadImage(const std::string);
    bool SaveImage(const std::string);
    void SetRotationAngleDegrees(double);
};

#endif
