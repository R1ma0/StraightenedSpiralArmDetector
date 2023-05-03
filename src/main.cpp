#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "detectorator.h"
#include "aliases.h"

namespace dsg = detectorator_namespace;

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Error : argc < 3" << std::endl;
		return 1;
	}
	std::filesystem::path pathReadImg {argv[1]};
	std::filesystem::path pathWriteImg {argv[2]};
	dsg::Detectorator detectorator;

	// Reading image
	cv::Mat sourceImg;
	detectorator.readImg(pathReadImg, sourceImg);

	// Processing image
	cv::Mat changedImg = sourceImg.clone(); 

	detectorator.setImgCompressPercentage(20.);
	detectorator.setBinaryThreshValue(127.);
	detectorator.setBinaryThreshMaxThreshValue(255.);
	detectorator.setGaussMaxThresh(255.);
	detectorator.setGaussConst(-9.);
	detectorator.setGaussBlockSize(111);
	detectorator.setThreshBinValue(128.);

	detectorator.execute(sourceImg, changedImg);

	// Writing image
	detectorator.writeImg(changedImg, pathWriteImg);
	//std::filesystem::path p(pathToImg);
	//std::string pathToSaveImg { + p.filename()};

	return 0;
}
