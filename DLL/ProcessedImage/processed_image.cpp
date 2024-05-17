#include "pch.h"
#include "processed_image.hpp"

ProcessedImage::ProcessedImage() {}

ProcessedImage::ProcessedImage(ProcessedImage* img)
{
    image = cv::Mat(img->GetProcessedImage());
}

cv::Mat ProcessedImage::GetProcessedImage()
{
    return image;
}

cv::Mat ProcessedImage::GetBaseImage()
{
    return baseImage;
}

cv::Mat ProcessedImage::GetRotatedImage()
{
    return rotatedImg;
}

cv::Size ProcessedImage::GetImageSize()
{
    return rotatedImg.size();
}

wxSize ProcessedImage::GetImageSizeWx()
{
    return wxSize(rotatedImg.size().width, rotatedImg.size().height);
}

int ProcessedImage::GetRotationAngleDegrees() const
{
    return rotationAngleDegrees;
}

void ProcessedImage::SetProcessedImage(cv::Mat img)
{
    image = img;
    isImageChanged = true;
}

void ProcessedImage::SetImageRotated()
{
    isImageRotated = true;
}

void ProcessedImage::SetImageChanged()
{
    isImageChanged = true;
}

bool ProcessedImage::IsImageChanged() const
{
    return isImageChanged;
}

bool ProcessedImage::IsImageRotated() const
{
    return isImageRotated;
}

bool ProcessedImage::LoadSrcImage(const std::string* path)
{
    cv::Mat img = cv::imread(*path);

    if (img.empty()) return true;

    if (img.channels() == 1) 
    {
        cv::cvtColor(img, image, cv::COLOR_GRAY2RGB); 
    }
    else if (img.channels() == 4) 
    {
        cv::cvtColor(img, image, cv::COLOR_BGRA2RGB); 
    }
    else 
    {
        cv::cvtColor(img, image, cv::COLOR_BGR2RGB); 
    }

    baseImage = cv::Mat(image);
    rotatedImg = cv::Mat(image);

    isImageChanged = false;
    isImageRotated = false;

    return false;
}

bool ProcessedImage::SaveImage(const std::string path)
{
    cv::Mat img;

    if (isImageChanged)
    {
        img = image;
    }
    else if (!isImageChanged && isImageRotated)
    {
        img = rotatedImg;
    }
    else
    {
        img = baseImage;
    }

    cv::cvtColor(img, img, cv::COLOR_RGB2BGR); 

    if (cv::imwrite(path, img)) return 1;
    else return 0;
}

void ProcessedImage::RotateImage(int angle)
{
    cv::Mat img = cv::Mat(baseImage);

    cv::Point2f imageCenter(
        (img.size().width) / 2.0, 
        (img.size().height) / 2.0
    );
    cv::Mat matrix = cv::getRotationMatrix2D(
        imageCenter, angle, 1.0
    );
    cv::Rect2f bbox = cv::RotatedRect(
        imageCenter, img.size(), angle
    ).boundingRect();

    matrix.at<double>(0, 2) += bbox.width / 2.0 - img.cols / 2.0;
    matrix.at<double>(1, 2) += bbox.height / 2.0 - img.rows / 2.0;

    cv::warpAffine(img, rotatedImg, matrix, bbox.size());

    rotationAngleDegrees = angle;
    isImageRotated = true;
}

void ProcessedImage::ResizeImage(int width, int height)
{
    cv::resize(rotatedImg, rotatedImg, cv::Size(width, height), cv::INTER_LINEAR);
    isImageRotated = true;
}