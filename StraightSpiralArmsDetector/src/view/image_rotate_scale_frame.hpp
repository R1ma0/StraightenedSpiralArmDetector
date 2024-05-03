#ifndef IMAGE_ROTATE_SCALE_FRAME_H
#define IMAGE_ROTATE_SCALE_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "grid_empty_cell.hpp"
#include "static_text_fonts.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/image_rotate_scale_frame_controller.hpp"

#ifndef IRSF
#define IRSF ImageRotateScaleFrame
#endif
#ifndef CastIRSF
#define CastIRSF dynamic_cast<ImageRotateScaleFrameController*>(controller)
#endif

class IRSF : public wxDialog
{
private:
    const int ANGLE_MIN_RANGE = -180;
    const int ANGLE_MAX_RANGE = 180;
    const unsigned int X_SCALE_MULT = 5;
    const unsigned int Y_SCALE_MULT = 5;
    wxSize baseImageSize;
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
    wxCheckBox* enableLivePreviewCB;
    wxSlider* angleSlider;
    wxSlider* scaleXNewSlider;
    wxSlider* scaleYNewSlider;
    bool isEnabledLivePreview = false;
    void CreateControls();
    void SetValuesAndRanges();
    void BindEventHandlers();
    void PerformProcessing();
    void IfEnableLivePreviewPerformProcessing();
    template <typename T, typename F> void UpdateValue(T*, F*);
    void OnApplyRotateScale(wxCommandEvent&);
    void OnEnableLivePreview(wxCommandEvent&);
    void OnAngleSpinChange(wxSpinEvent&);
    void OnAngleSliderChange(wxCommandEvent&);
    void OnNewScaleXSpinChange(wxSpinEvent&);
    void OnNewScaleXSliderChange(wxCommandEvent&);
    void OnNewScaleYSpinChange(wxSpinEvent&);
    void OnNewScaleYSliderChange(wxCommandEvent&);
public:
    IRSF(IController*);
    ~IRSF();
};

#endif
