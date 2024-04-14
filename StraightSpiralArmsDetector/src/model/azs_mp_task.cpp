#include "azs_mp_task.hpp"

AZSTasks* CreateSetOfTasks(
	SrcFilesData* srcFiles, 
	wxString dstDirPath, 
	AZSParametersRanges ranges
)
{
    AZSTasks* tasks = new AZSTasks();
	cv::Mat inImg;
    std::filesystem::path pathToImg;
    std::string extension;
    std::string filename;

    for (
        auto imgPath{ srcFiles->files.begin() };
        imgPath != srcFiles->files.end();
        imgPath++
    )
    {
        pathToImg = { std::string(*imgPath) };
        extension = pathToImg.extension().u8string();
        filename = pathToImg.stem().u8string();

        inImg = cv::imread(cv::String(*imgPath), cv::IMREAD_GRAYSCALE);

        for (
            int gbs = ranges.min.gaussBlockSize;
            gbs <= ranges.max.gaussBlockSize;
            gbs += ranges.step.gaussBlockSize
        )
        {
            for (
                float gc = ranges.min.gaussConst;
                gc <= ranges.max.gaussConst;
                gc += ranges.step.gaussConst
            )
            {
                for (
                    float icp = ranges.min.imgCompressPercentage;
                    icp <= ranges.max.imgCompressPercentage;
                    icp += ranges.step.imgCompressPercentage
                )
                {
                    for (
                        float btv = ranges.min.binaryThreshValue;
                        btv <= ranges.max.binaryThreshValue;
                        btv += ranges.step.binaryThreshValue
                    )
                    {
                    	AdaptiveZhangSuenParameters p{ 
                    		btv, gc, icp, gbs
                    	};

                    	AZSTask task{
                    		inImg,
                    		p,
                    		GetPathToSave(
                    			dstDirPath.utf8_string(),
                    			filename,
                    			extension,
                    			ParamsSeqToStr(&p)
                    		)
                        };

                        tasks->push_back(task);
                    }
                }
            }
        }
    }

	return tasks;
}

std::string GetPathToSave(
    std::string dstPath,
    std::string filename,
    std::string extension,
    std::string paramsStr
)
{
    std::filesystem::path pathToSave{ dstPath };

    pathToSave += std::string(
        "/_" + filename + "_" + paramsStr + extension
    );

    return pathToSave.u8string();
}

std::string ParamsSeqToStr(AdaptiveZhangSuenParameters* p)
{
    std::string btvStr = std::to_string(int(p->binaryThreshValue));
    std::string gcStr = std::to_string(int(p->gaussConst));
    std::string icpStr = std::to_string(int(p->imgCompressPercentage));
    std::string gbsStr = std::to_string(int(p->gaussBlockSize));

    return btvStr + "_" + gcStr + "_" + icpStr + "_" + gbsStr;
}