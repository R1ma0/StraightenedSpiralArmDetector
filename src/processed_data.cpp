#include "processed_data.h"

namespace processed_data_namespace
{
	ProcessedData::ProcessedData(fs::path cfg, uint filesCount)
	{
		readConfigFile(cfg);
		calcTotalOutputPerFile();
		calcTotalOutput(filesCount);
	}

	void ProcessedData::readConfigFile(fs::path pathToFile)
	{
		float min;
		float max;
		float step;
		std::string skip;
		std::ifstream file(pathToFile);

		if (file.is_open())
		{
			std::getline(file, skip, ':');
			file >> min; 
			binaryThreshValue.setMin(min);
			std::getline(file, skip, ':');
			file >> max;
			binaryThreshValue.setMax(max);
			std::getline(file, skip, ':');
			file >> step;
			binaryThreshValue.setStep(step);
			std::getline(file, skip, '$');
			
			std::getline(file, skip, ':');
			file >> min;
			gaussConst.setMin(min);
			std::getline(file, skip, ':');
			file >> max;
			gaussConst.setMax(max);
			std::getline(file, skip, ':');
			file >> step;
			gaussConst.setStep(step);
			std::getline(file, skip, '$');
			
			std::getline(file, skip, ':');
			file >> min;
			imgCompressPercentage.setMin(min);
			std::getline(file, skip, ':');
			file >> max;
			imgCompressPercentage.setMax(max);
			std::getline(file, skip, ':');
			file >> step;
			imgCompressPercentage.setStep(step);
			std::getline(file, skip, '$');
			
			std::getline(file, skip, ':');
			file >> min;
			gaussBlockSize.setMin(min);
			std::getline(file, skip, ':');
			file >> max;
			gaussBlockSize.setMax(max);
			std::getline(file, skip, ':');
			file >> step;
			gaussBlockSize.setStep(step);
			std::getline(file, skip, '$');
		}

		file.close();
	}

	void ProcessedData::calcTotalOutputPerFile()
	{
		totalOutputPerFile = binaryThreshValue.getIterRange() * 
							 gaussConst.getIterRange() *
							 imgCompressPercentage.getIterRange() *
							 gaussBlockSize.getIterRange();
	}

	void ProcessedData::calcTotalOutput(uint filesCount)
	{
		totalOutput = filesCount * totalOutputPerFile;
	}

	void ProcessedData::saveProcessedParameters(
		float gaussBlockSize, float gaussConstant, float imgCompressPercentage,
		float binaryThreshValue, std::string srcPath, std::string outPath
	)
	{
		imgProcParams.push_back(
			ImgProcessingParameters{
				gaussBlockSize, gaussConstant, imgCompressPercentage,
				binaryThreshValue, srcPath, outPath
			}
		);
	}

	void ProcessedData::writeProcessedParametersToXML(fs::path pathToXML)
	{
		tinyxml2::XMLDocument xmlDoc;

		tinyxml2::XMLNode *root = xmlDoc.NewElement("processing_results");
		xmlDoc.InsertFirstChild(root);

		for (auto i : imgProcParams)
		{
			tinyxml2::XMLElement *element = xmlDoc.NewElement("result");
			
			tinyxml2::XMLElement *content = xmlDoc.NewElement("src_path");
			content->SetText((i.srcPath).c_str());
			element->InsertEndChild(content);

			content = xmlDoc.NewElement("out_path");
			content->SetText((i.outPath).c_str());
			element->InsertEndChild(content);

			content = xmlDoc.NewElement("binary_thresh_value");
			content->SetText(i.binaryThreshValue);
			element->InsertEndChild(content);

			content = xmlDoc.NewElement("gauss_const");
			content->SetText(i.gaussConst);
			element->InsertEndChild(content);

			content = xmlDoc.NewElement("img_compress_percentage");
			content->SetText(i.imgCompressPercentage);
			element->InsertEndChild(content);

			content = xmlDoc.NewElement("gauss_block_size");
			content->SetText(i.gaussBlockSize);
			element->InsertEndChild(content);

			root->InsertEndChild(element);
		}

		xmlDoc.SaveFile(pathToXML.c_str());
	}

	pp::ProcessedParameters ProcessedData::getBinaryThreshValueParams()
	{
		return binaryThreshValue;
	}

	pp::ProcessedParameters ProcessedData::getGaussConstParams()
	{
		return gaussConst;
	}

	pp::ProcessedParameters ProcessedData::getImgCompressPercentageParams()
	{
		return imgCompressPercentage;
	}

	pp::ProcessedParameters ProcessedData::getGaussBlockSizeParams()
	{
		return gaussBlockSize;
	}
}
