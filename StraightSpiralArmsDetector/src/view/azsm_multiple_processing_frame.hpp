#ifndef AZSM_MULTIPLE_PROCESSING_FRAME_H
#define AZSM_MULTIPLE_PROCESSING_FRAME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "utils/grid_empty_cell.hpp"
#include "utils/static_text_fonts.hpp"
#include "../model/odd_even_checker.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen_types.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/azsm_multiple_processing_frame_controller.hpp"

#ifndef AZSMMPF
#define AZSMMPF AZSMMultipleProcessingFrame
#endif
#ifndef CastAZSMMPFC
#define CastAZSMMPFC dynamic_cast<AZSMMultipleProcessingFrameController*>(controller)
#endif

class AZSMMPF : public wxDialog
{
private:
    IController* controller;
    wxStaticText* srcFolderLabel;
    wxStaticText* dstFolderLabel;
    wxStaticText* binaryThreshValueLabel;
    wxStaticText* gaussConstLabel;
    wxStaticText* imgCompressPercentageLabel;
    wxStaticText* gaussBlockSizeLabel;
    wxStaticText* parameterLabel;
    wxStaticText* parameterMinLabel;
    wxStaticText* parameterMaxLabel;
    wxStaticText* parameterStepLabel;
    wxDirPickerCtrl* srcDirPicker;
    wxDirPickerCtrl* dstDirPicker;
    wxSpinCtrl* binaryThreshMinSpin;
    wxSpinCtrl* binaryThreshMaxSpin;
    wxSpinCtrl* binaryThreshStepSpin;
    wxSpinCtrl* gaussConstMinSpin;
    wxSpinCtrl* gaussConstMaxSpin;
    wxSpinCtrl* gaussConstStepSpin;
    wxSpinCtrl* imgCompressMinSpin;
    wxSpinCtrl* imgCompressMaxSpin;
    wxSpinCtrl* imgCompressStepSpin;
    wxSpinCtrl* gaussBlockMinSpin;
    wxSpinCtrl* gaussBlockMaxSpin;
    wxSpinCtrl* gaussBlockStepSpin;
    wxButton* startProcessing;
    int gbsMinOldValue;
    int gbsMaxOldValue;
    int gbsStepOldValue;
    void CreateControls();
    void BindEventHandlers();
    void OnStartProcess(wxCommandEvent&);
    void OnSetBinaryThreshMinSpin(wxCommandEvent&);
    void OnSetGaussConstMinSpin(wxCommandEvent&);
    void OnSetImgCompressPercentageMinSpin(wxCommandEvent&);
    void OnSetGaussBlockSizeMin(wxCommandEvent&);
    void OnSetGaussBlockSizeMax(wxCommandEvent&);
    void OnSetGaussBlockSizeStep(wxCommandEvent&);
    void OnSrcDirPickerChanged(wxCommandEvent&);
    void OnDstDirPickerChanged(wxCommandEvent&);
    void SetSpinRangeAndValue(wxSpinCtrl*, int, int, int);
public:
    AZSMMPF(IController*);
    ~AZSMMPF();
    const std::string DIR_DEFAULT_PATH{ "C:\\" };
    void SetStartProcessingBtnEnable(bool);
    int GetBTVMin() { return binaryThreshMinSpin->GetValue(); };
    int GetBTVMax() { return binaryThreshMaxSpin->GetValue(); };
    int GetBTVStep() { return binaryThreshStepSpin->GetValue(); };
    int GetGCMin() { return gaussConstMinSpin->GetValue(); };
    int GetGCMax() { return gaussConstMaxSpin->GetValue(); };
    int GetGCStep() { return gaussConstStepSpin->GetValue(); };
    int GetICPMin() { return imgCompressMinSpin->GetValue(); };
    int GetICPMax() { return imgCompressMaxSpin->GetValue(); };
    int GetICPStep() { return imgCompressStepSpin->GetValue(); };
    int GetGBSMin() { return gaussBlockMinSpin->GetValue(); };
    int GetGBSMax() { return gaussBlockMaxSpin->GetValue(); };
    int GetGBSStep() { return gaussBlockStepSpin->GetValue(); };
};

#endif
