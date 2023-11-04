#include "processed_image.hpp"

bool ProcessedImage::LoadImage(const std::string path)
{
    image = cv::imread(path, cv::IMREAD_COLOR);

    if (image.empty()) return 1;
    else return 0;
}

void ProcessedImage::SetRotationAngleDegrees(double degrees)
{
    if (degrees < 0 || degrees > 360) return;

    rotationAngleDegrees = degrees;
}
