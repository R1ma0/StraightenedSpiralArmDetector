#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include "detectorator.h"
#include "aliases.h"
#include "processed_data.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;
namespace pd = processed_data_namespace;

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

	pd::ProcessedData procData {pd::ProcessedData(pathToConfig)};
	std::vector<float> BTVParams = procData.getBinaryThreshValueParams();
	std::vector<float> GCParams = procData.getGaussConstParams();
	std::vector<float> ICPParams = procData.getImgCompressPercentageParams();
	std::vector<float> GBSParams = procData.getGaussBlockSizeParams();

	unsigned int totalDirFiles {getDirFilesCount(pathReadFolder)};
	unsigned int currentDirFile = 1;
	unsigned int totalOutputPerFile {procData.calcTotalOutputPerFile()};
	unsigned int currentOutputPerFile;
	unsigned int totalOutput = totalDirFiles * totalOutputPerFile;
	unsigned int currentOutput = 0;

	std::cout << "=== INFORMATION ===" << std::endl;
	std::cout << "+ " << totalDirFiles << " images will be processed" << std::endl;
	std::cout << "+ " << totalOutputPerFile;
	std::cout << " processed copies will be created for each image" << std::endl;
	std::cout << "+ " << totalOutput << " processed " << "images will be created" << std::endl;
	std::cout << "=== PROCESSING BEGIN ===" << std::endl;

	for (const auto &file : fs::directory_iterator(pathReadFolder))
	{
		std::string pathToFile {std::string(file.path())};
		currentOutputPerFile = 0;

		for (float i = GBSParams[0]; i < GBSParams[1]; i += GBSParams[2])
		{
			for (float j = GCParams[0]; j < GCParams[1]; j += GCParams[2])
			{
				for (float k = ICPParams[0]; k < ICPParams[1]; k += ICPParams[2])
				{
					for (float q = BTVParams[0]; q < BTVParams[1]; q += BTVParams[2])
					{
						std::cout << "+ [" << currentDirFile << "/" << totalDirFiles << "] ";
						std::cout << "[" << ++currentOutputPerFile << "/" << totalOutputPerFile << "] " ;
						std::cout << "[" << ++currentOutput << "/" << totalOutput << "] ";
						std::cout << "processing: ";
						std::cout << pathToFile << std::endl;
						
						// Reading image
						detectorator.readImg(file.path());
					
						// Processing image
						detectorator.setImgCompressPercentage(k);
						detectorator.setBinaryThreshValue(q);
						detectorator.setGaussConst(j);
						detectorator.setGaussBlockSize(i);
						
						detectorator.execute();
					
						// Writing image
						fs::path p(file.path().filename());
						std::string number {
							std::to_string(currentDirFile) + "_" + 
							std::to_string(currentOutputPerFile) + "_"
						};
						std::string filename {number + "changed_" + std::string(p)};
						fs::path saveTo {pathWriteFolder / filename};
						detectorator.writeImg(saveTo);
					}
				}
			}
		}

		currentDirFile++;
	}

	std::cout << "=== PROCESSING COMPLETED ===" << std::endl;

	return 0;
}

unsigned int getDirFilesCount(fs::path dir)
{
	return std::distance(fs::directory_iterator(dir), fs::directory_iterator{});
}
