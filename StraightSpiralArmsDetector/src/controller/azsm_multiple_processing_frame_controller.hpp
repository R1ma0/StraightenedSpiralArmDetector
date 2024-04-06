#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER
#define AZSM_MULTIPLE_PROCESSING_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "i_controller.hpp"

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
};

#endif
