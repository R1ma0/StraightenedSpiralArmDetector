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
#include "grid_empty_cell.hpp"


#ifndef IRSF
#define IRSF ImageRotateScaleFrame
#endif
#ifndef CastIRSF
#define CastIRSF dynamic_cast<ImageRotateScaleFrameController*>(controller)
#endif

class IRSF : public wxDialog
{
private:
    IController* controller;
    wxStaticText* rotateOldValue;
    wxStaticText* scaleXOldValue;
    wxStaticText* scaleYOldValue;
    wxStaticText* rotateTitle;
    wxStaticText* rotateOldText;
    wxStaticText* angleSpinNewText;
    wxStaticText* angleSpinText;
    wxStaticText* scaleTitle;
    wxStaticText* scaleXOldText;
    wxStaticText* scaleXNewText;
    wxStaticText* scaleYOldText;
    wxStaticText* scaleYNewText;
    wxSpinCtrl* angleSpin;
    wxSpinCtrl* scaleXNewSpin;
    wxSpinCtrl* scaleYNewSpin;
    wxButton* applyChangesBtn;
    unsigned int xScaleMult;
    unsigned int yScaleMult;
    void CreateControls();
    void SetValuesAndRanges();
    void BindEventHandlers();
    void SetBoldFont(wxStaticText*);
    void OnApplyRotateScale(wxCommandEvent&);
public:
    IRSF(IController*);
    ~IRSF();
};

#endif
