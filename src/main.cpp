#include <opencv2/imgcodecs.hpp>
#include "detectorator.h"

namespace dsg = detectorator_namespace;

int main(int argc, char** argv)
{
	std::filesystem::path pathToImage{argv[1]};
	
	// Reading image
	cv::Mat sourceImage{cv::imread(pathToImage, cv::IMREAD_GRAYSCALE)};
	if (sourceImage.empty())
	{
		std::cout << "FAILED. Could not read the image :" << pathToImage << std::endl;
		return 1;
	}

	// Processing image
	dsg::Detectorator detectorator;
	cv::Mat changedImage; 
	detectorator.execute(sourceImage, changedImage);

	// Saving image
	std::filesystem::path p(pathToImage);
	std::string pathToSaveImg {p.filename()};
	bool isImageWrite {cv::imwrite("changed_" + pathToSaveImg, changedImage)};
	if (!isImageWrite)
	{
		std::cout << "FAILED. The image was not saved : " << std::endl;
		return 1;
	}
	else
	{
		std::cout << "SUCCESSFULL image saved." << std::endl;
	}

	return 0;
}
