#include "azsm_multiple_processing_frame_controller.hpp"

AZSMMPFC::AZSMMPFC()
{
}

void AZSMMPFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMMPFC::MakeProcessing(
    AZSParametersRanges params, wxString srcDir, wxString dstDir
)
{
    
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
}