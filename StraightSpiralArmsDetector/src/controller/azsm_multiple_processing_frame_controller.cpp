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
    cv::Mat inImg;
    std::filesystem::path pathToImg;
    std::string paramsStr;
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
            float gbs = ranges.min.gaussBlockSize;
            gbs <= ranges.max.gaussBlockSize;
            gbs += ranges.step.gaussBlockSize
            )
        {
            azsParams->gaussBlockSize = gbs;

            for (
                float gc = ranges.min.gaussConst;
                gc <= ranges.max.gaussConst;
                gc += ranges.step.gaussConst
                )
            {
                azsParams->gaussConst = gc;

                for (
                    float icp = ranges.min.imgCompressPercentage;
                    icp <= ranges.max.imgCompressPercentage;
                    icp += ranges.step.imgCompressPercentage
                    )
                {
                    azsParams->imgCompressPercentage = icp;

                    for (
                        float btv = ranges.min.binaryThreshValue;
                        btv <= ranges.max.binaryThreshValue;
                        btv += ranges.step.binaryThreshValue
                        )
                    {
                        azsParams->binaryThreshValue = btv;

                        outImg = azsm->execute(inImg, *azsParams);

                        paramsStr = ParamsSeqToStr(azsParams);

                        cv::imwrite(
                            GetPathToSave(
                                std::string(dstDirPath),
                                filename,
                                extension,
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
    std::string filename,
    std::string extension,
    std::string paramsStr
)
{
    std::filesystem::path pathToSave{ dstPath };

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

bool AZSMMPFC::IsFolderHasFiles(wxString dir, std::vector<wxString> formats)
{
    wxDir d(dir);

    if (!d.IsOpened())
    {
        return false;
    }

    bool isContainFiles = true;

    for (auto format{ formats.begin() }; format != formats.end(); format++)
    {
        isContainFiles = d.HasFiles(*format);
    }

    return isContainFiles;
}

wxString AZSMMPFC::GetFileFormatsStr()
{
    wxString formats = "";

    for (
        auto format{ cts::IN_FILE_FORMATS.begin() };
        format != cts::IN_FILE_FORMATS.end();
        format++
        )
    {
        formats += *format;
    }

    return formats;
}