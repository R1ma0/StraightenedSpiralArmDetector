#ifndef IMAGE_ROTATE_SCALE_FRAME_H
#define IMAGE_ROTATE_SCALE_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "../model/processed_image.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/image_rotate_scale_frame_controller.hpp"

class ImageRotateScaleFrame : public wxFrame
{
private:
    IController *controller;
    wxStaticText *rotateOldValue;
    wxStaticText *scaleXOldValue;
    wxStaticText *scaleYOldValue;
    wxSpinCtrl *angleSpin;
    wxSpinCtrl *scaleXNewSpin;
    wxSpinCtrl *scaleYNewSpin;
    unsigned int xScaleMult;
    unsigned int yScaleMult;
    void CreateControls();
    void SetValuesAndRanges();
    void BindEventHandlers();
    void SetBoldFont(wxStaticText *);
public:
    ImageRotateScaleFrame(IController *);
};

#endif
