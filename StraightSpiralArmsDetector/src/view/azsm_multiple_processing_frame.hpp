#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_H
#define AZSM_MULTIPLE_PROCESSING_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "ids_of_controls.hpp"
#include "../controller/i_controller.hpp"

#ifndef AZSMMPF
#define AZSMMPF AZSMMultipleProcessingFrame
#endif

class AZSMMPF : public wxDialog
{
private:
    IController* controller;
    void CreateControls();
    void BindEventHandlers();
public:
    AZSMMPF(IController*);
    ~AZSMMPF();
};

#endif
