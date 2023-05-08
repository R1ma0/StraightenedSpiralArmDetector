#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "detectorator.h"
#include "aliases.h"
#include "config.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;
namespace cfgn = config_namespace;

unsigned int getDirFilesCount(fs::path);

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
	cfgn::Config config {cfgn::Config(pathToConfig)};
	unsigned int totalDirFiles = getDirFilesCount(pathReadFolder);
	unsigned int currentDirFile = 0;

	for (const auto &file : fs::directory_iterator(pathReadFolder))
	{
		std::string pathToFile {std::string(file.path())};
		cv::Mat sourceImg;

		std::cout << "+ [" << ++currentDirFile << "/" << totalDirFiles << "] ";
		std::cout << "processing: ";
		std::cout << pathToFile << std::endl;

		// Reading image
		detectorator.readImg(file.path(), sourceImg);
	
		// Processing image
		cv::Mat changedImg = sourceImg.clone(); 
	
		detectorator.setImgCompressPercentage(20.);
		detectorator.setBinaryThreshValue(127.);
		detectorator.setGaussConst(-9.);
		detectorator.setGaussBlockSize(111);
		detectorator.setThreshBinValue(128.);
		
		detectorator.execute(sourceImg, changedImg);
	
		// Writing image
		fs::path p(file.path().filename());
		std::string filename {"changed_" + std::string(p)};
		fs::path saveTo {pathWriteFolder / filename};
		detectorator.writeImg(changedImg, saveTo);
	}

	return 0;
}

unsigned int getDirFilesCount(fs::path dir)
{
	return std::distance(fs::directory_iterator(dir), fs::directory_iterator{});
}
