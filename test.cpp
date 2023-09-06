#include <opencv2/opencv.hpp>
#include <iostream>
#include "lib/detectorator.hpp"
#include "lib/adaptive_zhang_suen.hpp"

int main(int argc, char **argv)
{
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
    AdaptiveZhangSuenMethod azs = AdaptiveZhangSuenMethod();
    AdaptiveZhangSuenParameters azsParams{
        190.f, -5.f, 20.f, 201,
    };
    image = azs.execute(image, azsParams);

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
