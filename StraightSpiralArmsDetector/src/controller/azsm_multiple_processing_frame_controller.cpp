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
    
}