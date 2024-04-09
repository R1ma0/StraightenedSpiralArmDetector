#include "azsm_multiple_processing_frame_controller.hpp"

AZSMMPFC::~AZSMMPFC()
{
    delete view;
}

void AZSMMPFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMMPFC::MakeProcessing()
{
    AZSParametersRanges ranges = GetRanges();
    wxString srcDirPath = CastAZSMMPF->GetSrcDirPath();
    wxString dstDirPath = CastAZSMMPF->GetDstDirPath();
    SrcFilesData* srcFiles = GetFilesList(srcDirPath, cts::IN_FILE_FORMATS);
    AdaptiveZhangSuenParameters* azsParams = new AdaptiveZhangSuenParameters();
    AdaptiveZhangSuenMethod* azsm = new AdaptiveZhangSuenMethod();
    cv::Mat outImg;
    
    for (
        auto imgPath{ srcFiles->files.begin() }; 
        imgPath != srcFiles->files.end();
        imgPath++
    )
    {
        for (
            float gbs = ranges.min.gaussBlockSize;
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
                        azsParams->binaryThreshValue = btv;
                        azsParams->gaussBlockSize = gbs;
                        azsParams->gaussConst = gc;
                        azsParams->imgCompressPercentage = icp;

                        outImg = cv::imread(cv::String(*imgPath), cv::IMREAD_GRAYSCALE);
                        outImg = azsm->execute(outImg, *azsParams);
                        
                        cv::imwrite(
                            GetPathToSave(
                                std::string(dstDirPath), 
                                std::string(*imgPath)
                            ).u8string(),
                            outImg
                        );
                    }
                }
            }
        }
    }

    delete srcFiles;
    delete azsParams;
    delete azsm;
}

std::filesystem::path AZSMMPFC::GetPathToSave(
    std::string dstPath, 
    std::string filePath
)
{
    std::filesystem::path pathToSave{ dstPath };
    std::filesystem::path srcPath{ filePath };
    pathToSave += std::string("/_" + srcPath.filename().u8string());

    return pathToSave;
}

void AZSMMPFC::CheckDirExist(wxDirPickerCtrl* picker)
{
    bool dirExist = wxDirExists(picker->GetPath());

    if (dirExist)
    {
        CastAZSMMPF->SetStartProcessingBtnEnable(true);
    }
    else
    {
        CastAZSMMPF->SetStartProcessingBtnEnable(false);
    }
}

AZSParametersRanges AZSMMPFC::GetRanges()
{
    AZSParametersRanges paramRanges{};

    paramRanges.min = AdaptiveZhangSuenParameters{
        float(CastAZSMMPF->GetBTVMin()),
        float(CastAZSMMPF->GetGCMin()),
        float(CastAZSMMPF->GetICPMin()),
        CastAZSMMPF->GetGBSMin()
    };
    paramRanges.max = AdaptiveZhangSuenParameters{
        float(CastAZSMMPF->GetBTVMax()),
        float(CastAZSMMPF->GetGCMax()),
        float(CastAZSMMPF->GetICPMax()),
        CastAZSMMPF->GetGBSMax()
    };
    paramRanges.step = AdaptiveZhangSuenParameters{
        float(CastAZSMMPF->GetBTVStep()),
        float(CastAZSMMPF->GetGCStep()),
        float(CastAZSMMPF->GetICPStep()),
        CastAZSMMPF->GetGBSStep()
    };

    return paramRanges;
}