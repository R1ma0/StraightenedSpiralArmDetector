#include "azsm_multiple_processing_frame_controller.hpp"

AZSMMPFC::~AZSMMPFC()
{
    wxDELETE(computeThread);
    wxDELETE(thPoolTasks);
    wxDELETE(srcFiles);
}

void AZSMMPFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMMPFC::MakeProcessing()
{
    activityIndicator = CreateActivityIndicator(view, wxSize(100, 100));
    activityIndicator->Start();
    activityIndicator->Show();
    EnableDialogComponents(false);

    wxString srcDirPath = CastAZSMMPF->GetSrcDirPath();
    wxString dstDirPath = CastAZSMMPF->GetDstDirPath();
    srcFiles = GetFilesList(srcDirPath, cts::IN_FILE_FORMATS);
    AZSParametersRanges ranges = GetRanges();

    computeThread = new std::thread{
        &AZSMMPFC::Compute,
        this,
        dstDirPath,
        ranges,
        activityIndicator
    };
    computeThread->detach();
}

void AZSMMPFC::Compute(
    wxString dstDirPath,
    AZSParametersRanges ranges,
    wxActivityIndicator* actInd
)
{
    ThreadPool* thPool = new ThreadPool();
    AdaptiveZhangSuenMethod* azsm = new AdaptiveZhangSuenMethod();

    thPoolTasks = CreateSetOfTasks(srcFiles, dstDirPath, ranges);

    for (
        auto task{ thPoolTasks->begin() };
        task != thPoolTasks->end();
        ++task
    )
    {
        thPool->Enqueue([task, azsm] {
            cv::Mat outImg = azsm->execute(task->img, task->params);
            cv::imwrite(task->pathToSave, outImg);
        });
    }

    while (!thPool->IsTasksEmpty())
    {
        thPool->~ThreadPool();

        actInd->Stop();
        actInd->Hide();
        EnableDialogComponents(true);
    }

    delete azsm;
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

    for (auto format{ formats.begin() }; format != formats.end(); format++)
    {
        if (d.HasFiles(*format))
        {
            return true;
        }
    }

    return false;
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