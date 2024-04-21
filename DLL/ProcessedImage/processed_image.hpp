#ifndef PROCESSED_IMAGE_H
#define PROCESSED_IMAGE_H

#ifdef _SSAD_PROCESSED_IMG_EXPORTS
#define SSAD_PROCESSED_IMG_API __declspec(dllexport)
#else
#define SSAD_PROCESSED_IMG_API __declspec(dllimport)
#endif

#include <opencv2/opencv.hpp>
#include <wx/image.h>
#include <vector>

class SSAD_PROCESSED_IMG_API ProcessedImage
{
private:
    cv::Mat image;
    int rotationAngleDegrees = 0;
public:
    cv::Mat GetProcessedImage();
    cv::Mat RotateImage(cv::Mat, int);
    cv::Size GetImageSize();
    int GetRotationAngleDegrees() const;
    bool LoadSrcImage(const std::string*);
    bool SaveImage(const std::string);
    void SetProcessedImage(cv::Mat);
};

#endif
