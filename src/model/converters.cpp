#include "converters.hpp"

wxImage MatToWxImage(cv::Mat img)
{
    if (img.channels() == 1) { cv::cvtColor(img, img, cv::COLOR_GRAY2RGB); }
    else if (img.channels() == 4) { cv::cvtColor(img, img, cv::COLOR_BGRA2RGB); }
    else { cv::cvtColor(img, img, cv::COLOR_BGR2RGB); }

    long imageSize = img.rows * img.cols * img.channels();

    wxImage image(img.cols, img.rows, (unsigned char *)malloc(imageSize), false);
    unsigned char *matData = img.data;
    unsigned char *wxData = image.GetData();

    for (long i = 0; i < imageSize; i++) { wxData[i] = matData[i]; }

    return image;
}
