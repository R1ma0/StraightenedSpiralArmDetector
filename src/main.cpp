#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include "detectorator.h"
#include "aliases.h"
#include "processed_data.h"
#include "processed_parameters.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;
namespace pd = processed_data_namespace;
namespace pp = processed_parameters_namespace;

uint getDirFilesCount(fs::path);
void displayInfoHeader(uint, uint, uint);
void displayInfo(uint, uint, uint, uint, uint, uint, std::string, fs::path);
void displayInfoFooter();

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

	uint totalDirFiles {getDirFilesCount(pathReadFolder)};
	uint currentDirFile = 1;

	pd::ProcessedData procData {pd::ProcessedData(pathToConfig, totalDirFiles)};
	pp::ProcessedParameters BTV = procData.getBinaryThreshValueParams();
	pp::ProcessedParameters GC = procData.getGaussConstParams();
	pp::ProcessedParameters ICP = procData.getImgCompressPercentageParams();
	pp::ProcessedParameters GBS = procData.getGaussBlockSizeParams();

	uint totalOutputPerFile {procData.getTotalOutputPerFile()};
	uint currentOutputPerFile;
	uint totalOutput {procData.getTotalOutput()};
	uint currentOutput = 0;

	displayInfoHeader(totalDirFiles, totalOutputPerFile, totalOutput);

	for (const auto &file : fs::directory_iterator(pathReadFolder))
	{
		std::string pathToFile {std::string(file.path())};
		currentOutputPerFile = 0;

		for (float i = GBS.getMin(); i < GBS.getMax(); i += GBS.getStep())
		{
			for (float j = GC.getMin(); j < GC.getMax(); j += GC.getStep())
			{
				for (float k = ICP.getMin(); k < ICP.getMax(); k += ICP.getStep())
				{
					for (float q = BTV.getMin(); q < BTV.getMax(); q += BTV.getStep())
					{
						// Path to save and filename
						fs::path p(file.path().filename());
						std::string number {
							std::to_string(currentDirFile) + "_" + 
							std::to_string(currentOutputPerFile + 1) + "_"
						};
						std::string filename {number + "changed_" + std::string(p)};
						fs::path saveTo {pathWriteFolder / filename};

						displayInfo(
							currentDirFile, totalDirFiles, ++currentOutputPerFile,
							totalOutputPerFile, ++currentOutput, totalOutput,
							file.path(), saveTo
						);

						// Reading image
						detectorator.readImg(file.path());
					
						// Processing image
						detectorator.setImgCompressPercentage(k);
						detectorator.setBinaryThreshValue(q);
						detectorator.setGaussConst(j);
						detectorator.setGaussBlockSize(i);
						
						detectorator.execute();
					
						// Writing image
						detectorator.writeImg(saveTo);

						procData.saveProcessedParameters(
							i, j, k, q, pathToFile, std::string(saveTo)
						);
					}
				}
			}
		}

		currentDirFile++;
	}
	
	procData.writeProcessedParametersToXML("processed_params.xml");
	displayInfoFooter();

	return 0;
}

uint getDirFilesCount(fs::path dir)
{
	return std::distance(fs::directory_iterator(dir), fs::directory_iterator{});
}

void displayInfoHeader(uint totalDirFiles, uint totalOutputPerFile, uint totalOutput)
{
	std::cout << "=== INFORMATION ===" << std::endl;
	std::cout << "+ " << totalDirFiles << " images will be processed" << std::endl;
	std::cout << "+ " << totalOutputPerFile;
	std::cout << " processed copies will be created for each image" << std::endl;
	std::cout << "+ " << totalOutput << " processed " << "images will be created" << std::endl;
	std::cout << "=== PROCESSING BEGIN ===" << std::endl;
}

void displayInfoFooter()
{
	std::cout << "=== PROCESSING COMPLETED ===" << std::endl;
}

void displayInfo(
	uint currentDirFile, uint totalDirFiles, uint currentOutputPerFile, 
	uint totalOutputPerFile, uint currentOutput, uint totalOutput, 
	std::string pathToFile, fs::path saveTo
)
{
	std::cout << "+ [" << currentDirFile << "/" << totalDirFiles << "] ";
	std::cout << "[" << currentOutputPerFile << "/" << totalOutputPerFile << "] " ;
	std::cout << "[" << currentOutput << "/" << totalOutput << "] ";
	std::cout << "processing: ";
	std::cout << pathToFile << " => " << saveTo << std::endl;
}
