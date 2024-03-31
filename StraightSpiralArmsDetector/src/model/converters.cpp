#include "converters.hpp"

wxImage MatToWxImage(cv::Mat* img)
{
    long imageSize = img->rows * img->cols * img->channels();

    wxImage image(
        img->cols, 
        img->rows, 
        (unsigned char*)malloc(imageSize), 
        false
    );
    unsigned char* matData = img->data;
    unsigned char* wxData = image.GetData();

    for (long i = 0; i < imageSize; i++) { wxData[i] = matData[i]; }

    return image;
}
