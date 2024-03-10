#ifndef PROCESSED_IMAGE_H
#define PROCESSED_IMAGE_H

#include <opencv2/opencv.hpp>
#include <wx/image.h>
#include <vector>

class ProcessedImage
{
private:
    cv::Mat image;
    int rotationAngleDegrees = 0;
public:
    cv::Mat GetProcessedImage();
    cv::Mat RotateImage(cv::Mat, int);
    cv::Size GetImageSize();
    int GetRotationAngleDegrees();
    bool LoadSrcImage(const std::string);
    bool SaveImage(const std::string);
    void SetProcessedImage(cv::Mat);
};

#endif
