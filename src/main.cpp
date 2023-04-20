#include <opencv2/imgcodecs.hpp>
#include "detectorator.h"

namespace dsg = detectorator_namespace;

int main(int argc, char** argv)
{
	std::filesystem::path pathReadImg {argv[1]};
	std::filesystem::path pathWriteImg {argv[2]};
	dsg::Detectorator detectorator;

	// Reading image
	cv::Mat sourceImg;
	detectorator.readImg(pathReadImg, sourceImg);

	// Processing image
	cv::Mat changedImg; 

	detectorator.setImgCompressPercentage(20.);
	detectorator.setGaussMaxThresh(255.);
	detectorator.setGaussConst(1.);
	detectorator.setGaussBlockSize(3);

	detectorator.execute(sourceImg, changedImg);

	// Writing image
	detectorator.writeImg(changedImg, pathWriteImg);
	//std::filesystem::path p(pathToImg);
	//std::string pathToSaveImg { + p.filename()};

	return 0;
}
