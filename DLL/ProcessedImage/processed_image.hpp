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
    cv::Mat baseImage;
    cv::Mat rotatedImg;
    int rotationAngleDegrees = 0;
    bool isImageRotated = false;
    bool isImageChanged = false;
public:
    ProcessedImage();
    ProcessedImage(ProcessedImage*);
    cv::Mat GetProcessedImage();
    cv::Mat GetBaseImage();
    cv::Mat GetRotatedImage();
    cv::Size GetImageSize();
    wxSize GetImageSizeWx();
    int GetRotationAngleDegrees() const;
    bool LoadSrcImage(const std::string*);
    bool SaveImage(const std::string);
    bool IsImageRotated() const;
    bool IsImageChanged() const;
    void SetImageRotated();
    void SetImageChanged();
    void SetProcessedImage(cv::Mat);
    void RotateImage(int);
    void ResizeImage(int, int);
};

#endif
