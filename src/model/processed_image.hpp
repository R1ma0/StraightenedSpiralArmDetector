#ifndef PROCESSED_IMAGE_H
#define PROCESSED_IMAGE_H

#include <opencv2/opencv.hpp>

class ProcessedImage
{
private:
    cv::Mat image;
public:
    cv::Mat GetProcessedImage() { return image; };
    bool LoadImage(const std::string);
};

#endif
