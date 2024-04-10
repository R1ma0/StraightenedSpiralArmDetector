#include "azsm_multiple_processing_frame_controller.hpp"

AZSMMPFC::~AZSMMPFC()
{
    delete view;
    delete activityIndicator;
    delete computeThread;
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

    activityIndicator = CreateActivityIndicator(view, wxSize(100, 100));
    activityIndicator->Start();
    activityIndicator->Show();

    EnableDialogComponents(false);

    computeThread = new std::thread{
        &AZSMMPFC::Compute,
        this,
        srcFiles,
        dstDirPath,
        azsm,
        ranges,
        azsParams,
        activityIndicator
    };
    computeThread->detach();
}

void AZSMMPFC::Compute(
    SrcFilesData* srcFiles,
    wxString dstDirPath,
    AdaptiveZhangSuenMethod* azsm,
    AZSParametersRanges ranges,
    AdaptiveZhangSuenParameters* azsParams,
    wxActivityIndicator* actInd
)
{
    cv::Mat outImg;
    std::string paramsStr;

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

                        paramsStr = ParamsSeqToStr(azsParams);

                        cv::imwrite(
                            GetPathToSave(
                                std::string(dstDirPath),
                                std::string(*imgPath),
                                paramsStr
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

    actInd->Stop();
    actInd->Hide();
    EnableDialogComponents(true);
}

std::filesystem::path AZSMMPFC::GetPathToSave(
    std::string dstPath, 
    std::string filePath,
    std::string paramsStr
)
{
    std::filesystem::path pathToSave{ dstPath };
    std::filesystem::path srcPath{ filePath };

    std::string extension = srcPath.extension().u8string();
    std::string filename = srcPath.stem().u8string();

    pathToSave += std::string(
        "/_" + filename + "_" + paramsStr + extension
    );

    return pathToSave;
}

std::string AZSMMPFC::ParamsSeqToStr(AdaptiveZhangSuenParameters* p)
{
    std::string btvStr = std::to_string(int(p->binaryThreshValue));
    std::string gcStr = std::to_string(int(p->gaussConst));
    std::string icpStr = std::to_string(int(p->imgCompressPercentage));
    std::string gbsStr = std::to_string(int(p->gaussBlockSize));

    return btvStr + "_" + gcStr + "_" + icpStr + "_" + gbsStr;
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

void AZSMMPFC::EnableDialogComponents(bool state)
{
    CastAZSMMPF->SetEnableComponents(state);
}