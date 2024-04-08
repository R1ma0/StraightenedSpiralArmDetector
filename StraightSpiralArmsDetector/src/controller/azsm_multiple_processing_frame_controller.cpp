#include "azsm_multiple_processing_frame_controller.hpp"

AZSMMPFC::AZSMMPFC()
{
}

void AZSMMPFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMMPFC::MakeProcessing()
{
    AZSParametersRanges ranges = GetRanges();
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