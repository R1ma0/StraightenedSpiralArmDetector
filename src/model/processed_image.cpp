#include "processed_image.hpp"

bool ProcessedImage::LoadImage(const std::string path)
{
    image = cv::imread(path);

    if (image.empty()) return 1;
    else return 0;
}

bool ProcessedImage::SaveImage(const std::string path)
{
    cv::Mat img;
    cv::cvtColor(image, img, cv::COLOR_BGR2RGB);

    if (cv::imwrite(path, img)) return 1;
    else return 0;
}

void ProcessedImage::SetRotationAngleDegrees(double degrees)
{
    if (degrees < 0 || degrees > 360) return;

    rotationAngleDegrees = degrees;
}
