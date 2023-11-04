#include "processed_image.hpp"

bool ProcessedImage::LoadImage(const std::string path)
{
    image = cv::imread(path, cv::IMREAD_COLOR);

    if (image.empty()) return 1;
    else return 0;
}
