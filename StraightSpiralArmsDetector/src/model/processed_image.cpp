#include "processed_image.hpp"

cv::Mat ProcessedImage::GetProcessedImage()
{
    return image;
}

cv::Size ProcessedImage::GetImageSize()
{
    return image.size();
}

int ProcessedImage::GetRotationAngleDegrees() const
{
    return rotationAngleDegrees;
}

void ProcessedImage::SetProcessedImage(cv::Mat img)
{
    image = img;
}

bool ProcessedImage::LoadSrcImage(const std::string path)
{
    cv::Mat img = cv::imread(path);

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

    return false;
}

bool ProcessedImage::SaveImage(const std::string path)
{
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR); 

    if (cv::imwrite(path, image)) return 1;
    else return 0;
}

cv::Mat ProcessedImage::RotateImage(cv::Mat image, int angle)
{
    cv::Point2f imageCenter(
        (image.size().width) / 2.0, 
        (image.size().height) / 2.0
    );
    cv::Mat matrix = cv::getRotationMatrix2D(
        imageCenter, angle, 1.0
    );
    cv::Rect2f bbox = cv::RotatedRect(
        cv::Point2f(), image.size(), angle
    ).boundingRect2f();

    matrix.at<double>(0, 2) += bbox.width / 2.0 - image.cols / 2.0;
    matrix.at<double>(1, 2) += bbox.height / 2.0 - image.rows / 2.0;

    cv::warpAffine(image, image, matrix, bbox.size());

    rotationAngleDegrees = angle;

    return image;
}
