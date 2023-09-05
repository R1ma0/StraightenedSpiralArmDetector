#include <opencv2/opencv.hpp>
#include <iostream>
#include "lib/detectorator.hpp"

int main(int argc, char **argv)
{
    Detectorator detectorator = Detectorator();
    cv::Mat image;

    // Reading file
    image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Could not open file: " << argv[1] << std::endl;
    }
    else
    {
        std::cout << "Processing: " << argv[1] << " ..." << std::endl;
    }

    // Processing file
    detectorator.setImage(image);
    detectorator.setBinaryThreshValue(190.f);
    detectorator.setImgCompressPercentage(20.f);
    detectorator.setGaussConst(-5.f);
    detectorator.setGaussBlockSize(201.f);
    detectorator.execute();
    image = detectorator.getImage();

    // Writing file
    if (!cv::imwrite(argv[2], image))
    {
        std::cout << "Could not write file: " << argv[2] << std::endl;
    }
    else
    {
        std::cout << "File: " << argv[2] << " saved!" << std::endl;
    }

    return 0;
}
