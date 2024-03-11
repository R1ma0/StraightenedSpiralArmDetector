#ifndef AZSM_CONTROL_FRAME_H
#define AZSM_CONTROL_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "buffered_bitmap.hpp"
#include "../model/processed_image.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/azsm_frame_controller.hpp"

class AZSMControlFrame : public wxFrame
{
private:
    IController *controller;
    wxSpinCtrl *binaryThreshValueSpin;
    wxSpinCtrl *gaussConstSpin;
    wxSpinCtrl *imgCompressPercentageSpin;
    wxSpinCtrl *gaussBlockSizeSpin;
    void CreateControls();
    void BindEventHandlers();
    void OnRunDetectorator(wxCommandEvent &);
public:
    AZSMControlFrame(IController *);
    int GetBinaryThresh() { return binaryThreshValueSpin->GetValue(); }
    int GetGaussConst() { return gaussConstSpin->GetValue(); }
    int GetCompressPercentage() { return imgCompressPercentageSpin->GetValue(); }
    int GetGaussBlockSize() { return gaussBlockSizeSpin->GetValue(); }
};

#endif
