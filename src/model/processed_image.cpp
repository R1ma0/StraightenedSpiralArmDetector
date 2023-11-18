#include "processed_image.hpp"

cv::Mat ProcessedImage::GetProcessedImage()
{
    return image;
}

double ProcessedImage::GetRotationAngleDegrees()
{
    return rotationAngleDegrees;
}

bool ProcessedImage::LoadImage(const std::string path)
{
    image = cv::imread(path);

    if (image.empty()) return true;

    if (image.channels() == 1) 
    {
        cv::cvtColor(image, image, cv::COLOR_GRAY2RGB); 
    }
    else if (image.channels() == 4) 
    {
        cv::cvtColor(image, image, cv::COLOR_BGRA2RGB); 
    }
    else 
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB); 
    }

    return false;
}

bool ProcessedImage::SaveImage(const std::string path)
{
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR); 

    if (cv::imwrite(path, image)) return 1;
    else return 0;
}

cv::Mat ProcessedImage::RotateImage(cv::Mat image, double angle)
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
