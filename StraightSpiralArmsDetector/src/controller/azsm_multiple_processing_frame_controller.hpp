#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER
#define AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen_types.hpp"

#ifndef AZSMMPFC
#define AZSMMPFC AZSMMultipleProcessingFrameController
#endif

class AZSMMPFC : public IController
{
private:
    wxWindow* view;
public:
    AZSMMPFC();
    void SetView(wxWindow*) override;
    void MakeProcessing(AZSParametersRanges);
};

#endif
