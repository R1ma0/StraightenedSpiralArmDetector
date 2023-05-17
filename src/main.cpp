#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include "detectorator.h"
#include "aliases.h"
#include "processed_data.h"
#include "processed_parameters.h"

namespace dsg = detectorator_namespace;
namespace fs = std::filesystem;
namespace pd = processed_data_namespace;
namespace pp = processed_parameters_namespace;

float calcDeltaTimeSec(clock_t &, clock_t &);
uint getDirFilesCount(fs::path);
bool displayInfoHeader(
	uint, uint, uint, 
	pp::ProcessedParameters &, pp::ProcessedParameters &,
	pp::ProcessedParameters &, pp::ProcessedParameters &
);
void displayInfo(
	uint, uint, uint, uint, uint, uint, 
	float &, float &, float &, float &, std::string
);

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
	std::string readedFilename;
	std::string filenameToSave;
	std::string saveFileTo;
	cv::Mat procImg;

	clock_t tStartProc;
	clock_t tEndProc;
	clock_t processingTimeStart;
	clock_t processingTimeEnd;
	float processingDeltaTime;

	pd::ProcessedData procData {pd::ProcessedData(pathToConfig, totalDirFiles)};
	pp::ProcessedParameters BTV = procData.getBinaryThreshValueParams();
	pp::ProcessedParameters GC = procData.getGaussConstParams();
	pp::ProcessedParameters ICP = procData.getImgCompressPercentageParams();
	pp::ProcessedParameters GBS = procData.getGaussBlockSizeParams();

	uint totalOutputPerFile {procData.getTotalOutputPerFile()};
	uint currentOutputPerFile;
	uint totalOutput {procData.getTotalOutput()};
	uint currentOutput = 0;

	bool startProc = displayInfoHeader(
		totalDirFiles, totalOutputPerFile, totalOutput, BTV, GC, ICP, GBS
	);
	if (!startProc)
		return 0;

	std::cout << "=== PROCESSING BEGIN ===" << std::endl;

	tStartProc = clock();

	for (const auto &file : fs::directory_iterator(pathReadFolder))
	{
		std::string pathToFile {std::string(file.path())};
		readedFilename = std::string(file.path().filename());
		currentOutputPerFile = 0;
		
		// Reading image
		detectorator.readImg(file.path());

		for (float i = GBS.getMin(); i <= GBS.getMax(); i += GBS.getStep())
		{
			for (float j = GC.getMin(); j <= GC.getMax(); j += GC.getStep())
			{
				for (float k = ICP.getMin(); k <= ICP.getMax(); k += ICP.getStep())
				{
					for (float q = BTV.getMin(); q <= BTV.getMax(); q += BTV.getStep())
					{
						currentOutput++;
						filenameToSave = std::to_string(currentOutput) + "_" + readedFilename;
						saveFileTo = pathWriteFolder / filenameToSave;

						displayInfo(
							currentDirFile, totalDirFiles, ++currentOutputPerFile,
							totalOutputPerFile, currentOutput, totalOutput,
							i, j, k, q, filenameToSave
						);

						// Processing image
						detectorator.setImgCompressPercentage(k);
						detectorator.setBinaryThreshValue(q);
						detectorator.setGaussConst(j);
						detectorator.setGaussBlockSize(i);
						
						processingTimeStart = clock();
						procImg = detectorator.execute();
						processingTimeEnd = clock();	

						processingDeltaTime = calcDeltaTimeSec(
							processingTimeStart, processingTimeEnd
						);
						std::cout << " Time : " << processingDeltaTime;
						std::cout << " sec." << std::endl;

						// Writing image
						detectorator.writeImg(procImg, saveFileTo);

						procData.saveProcessedParameters(
							i, j, k, q, processingDeltaTime, pathToFile, saveFileTo
						);
					}
				}
			}
		}

		currentDirFile++;
	}

	tEndProc = clock();
	std::cout << "Time remain : " << calcDeltaTimeSec(tStartProc, tEndProc)/60.0;
	std::cout << " min." << std::endl;
	
	procData.writeProcessedParametersToXML("processed_params.xml");
	std::cout << "=== PROCESSING COMPLETED ===" << std::endl;

	return 0;
}

float calcDeltaTimeSec(clock_t &start, clock_t &end)
{
	return (float)(end - start) / CLOCKS_PER_SEC;
}

uint getDirFilesCount(fs::path dir)
{
	return std::distance(fs::directory_iterator(dir), fs::directory_iterator{});
}

bool displayInfoHeader(
	uint totalDirFiles, uint totalOutputPerFile, uint totalOutput, 
	pp::ProcessedParameters &BTV, pp::ProcessedParameters &GC,
	pp::ProcessedParameters &ICP, pp::ProcessedParameters &GBS
)
{
	bool status = false;
	std::string userInput = "";

	std::cout << "=== INFORMATION ===" << std::endl;
	std::cout << "+ " << totalDirFiles << " images will be processed" << std::endl;
	std::cout << "+ " << totalOutputPerFile;
	std::cout << " processed copies will be created for each image" << std::endl;
	std::cout << "+ " << totalOutput << " processed " << "images will be created" << std::endl;
	
	std::cout << "Processed data:" << std::endl;
	std::cout << "+ Gauss Block Size: ";
	std::cout << "min = "   << GBS.getMin()       << "; ";
	std::cout << "max = "   << GBS.getMax()       << "; ";
	std::cout << "step = "  << GBS.getStep()      << "; ";
	std::cout << "range = " << GBS.getIterRange() << std::endl;
	std::cout << "+ Binary Thresh Value: ";
	std::cout << "min = "   << BTV.getMin()		  << "; ";
	std::cout << "max = "   << BTV.getMax()		  << "; ";
	std::cout << "step = "  << BTV.getStep()	  << "; ";
	std::cout << "range = " << BTV.getIterRange() << std::endl;
	std::cout << "+ Image Compress Percentage: ";
	std::cout << "min = "   << ICP.getMin()		  << "; ";
	std::cout << "max = "   << ICP.getMax()		  << "; ";
	std::cout << "step = "  << ICP.getStep()	  << "; ";
	std::cout << "range = " << ICP.getIterRange() << std::endl;
	std::cout << "+ Gauss Constant: ";
	std::cout << "min = "   << GC.getMin()		  << "; ";
	std::cout << "max = "   << GC.getMax()		  << "; ";
	std::cout << "step = "  << GC.getStep()		  << "; ";
	std::cout << "range = " << GC.getIterRange()  << std::endl;
	
	std::cout << "Start image processing? [Y/N]" << std::endl;
	std::cin >> userInput;
	if (!userInput.compare("y") || !userInput.compare("Y"))
		status = true;

	return status;
}

void displayInfo(
	uint currentDirFile, uint totalDirFiles, uint currentOutputPerFile, 
	uint totalOutputPerFile, uint currentOutput, uint totalOutput, 
	float &GBS, float &GC, float &ICP, float &BTV, std::string outFilename
)
{
	std::cout << "+ [" << currentDirFile << "/" << totalDirFiles << "] ";
	std::cout << "[" << currentOutputPerFile << "/" << totalOutputPerFile << "] " ;
	std::cout << "[" << currentOutput << "/" << totalOutput << "] ";
	std::cout << "Parameters: " << "GBS=" << GBS << "; GC=" << GC;
	std::cout << "; ICP=" << ICP << "; BTV=" << BTV << " => ";
	std::cout << outFilename << ";";
}
