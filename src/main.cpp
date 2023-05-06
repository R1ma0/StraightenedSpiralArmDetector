#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "detectorator.h"
#include "aliases.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;

void pMsg(std::string msg, std::string type="")
{
	std::cout << type << msg << std::endl;
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Error : argc < 4" << std::endl;
		return 1;
	}

	fs::path pathReadFolder {argv[1]};
	fs::path pathWriteFolder {argv[2]};
	fs::path pathToConfig {argv[3]};
	fs::path pathWriteImg;
	dsg::Detectorator detectorator;
	dsg::Config config {dsg::Config(pathToConfig)};

	for (const auto &file : fs::directory_iterator(pathReadFolder))
	{
		std::string pathToFile {std::string(file.path())};
		cv::Mat sourceImg;

		// Reading image
		pMsg(pathToFile, " + Reading a file : ");
		detectorator.readImg(file.path(), sourceImg);
	
		// Processing image
		cv::Mat changedImg = sourceImg.clone(); 
	
		detectorator.setImgCompressPercentage(20.);
		detectorator.setBinaryThreshValue(127.);
		detectorator.setGaussConst(-9.);
		detectorator.setGaussBlockSize(111);
		detectorator.setThreshBinValue(128.);
		
		pMsg(pathToFile, " + Starting file processing : ");
		detectorator.execute(sourceImg, changedImg);
		pMsg(pathToFile, " + Finishing file processing : ");
	
		// Writing image
		fs::path p(file.path().filename());
		std::string filename {"changed_" + std::string(p)};
		fs::path saveTo {pathWriteFolder / filename};
		pMsg(pathToFile, " + Writing a file : ");
		detectorator.writeImg(changedImg, saveTo);
	}

	return 0;
}
