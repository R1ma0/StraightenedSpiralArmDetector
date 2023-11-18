#include "detectorator_control_panel.hpp"

DetectoratorControlPanel::DetectoratorControlPanel
(
    wxFrame *parentFrame, 
    BufferedBitmap *bitmap,
    ProcessedImage *procImage
) : wxPanel(parentFrame)
{
    this->bitmap = bitmap;
    this->procImage = procImage;

    CreateControls();
    BindEventHandlers();
}

void DetectoratorControlPanel::CreateControls()
{
    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto binaryThreshValueLabel = new wxStaticText(
        this, -1, wxT("Binary Thresh Value:")
    );
    sizer->Add(binaryThreshValueLabel, 0, wxTOP | wxRIGHT, FromDIP(10));

    auto binaryThreshValueSpin = new wxSpinCtrl(this);
    sizer->Add(
        binaryThreshValueSpin, 0, wxEXPAND | wxTOP | wxRIGHT, FromDIP(10)
    );

    auto gaussConstLabel = new wxStaticText(
        this, -1, wxT("Gauss Constant Value:")        
    );
    sizer->Add(gaussConstLabel, 0, wxTOP | wxRIGHT, FromDIP(10));

    auto gaussConstSpin = new wxSpinCtrl(this);
    sizer->Add(
        gaussConstSpin, 0, wxEXPAND |  wxTOP | wxRIGHT, FromDIP(10)
    );

    auto imgCompressPercentageLabel = new wxStaticText(
        this, -1, wxT("Image Compress Percentage:")
    );
    sizer->Add(imgCompressPercentageLabel, 0, wxTOP | wxRIGHT, FromDIP(10));

    auto imgCompressPercentageSpin = new wxSpinCtrl(this);
    sizer->Add(
        imgCompressPercentageSpin, 0, wxEXPAND | wxTOP | wxRIGHT, FromDIP(10)
    );

    auto gaussBlockSizeLabel = new wxStaticText(
        this, -1, wxT("Gauss Block Size Value: ")        
    );
    sizer->Add(gaussBlockSizeLabel, 0, wxTOP | wxRIGHT, FromDIP(10));

    auto gaussBlockSizeSpin = new wxSpinCtrl(this);
    sizer->Add(gaussBlockSizeSpin, 0, wxEXPAND |  wxTOP | wxRIGHT, FromDIP(10));

    auto computeBtn = new wxButton(this, ID_RUN_DETECTORATOR, wxT("Compute"));
    sizer->Add(computeBtn, 0, wxEXPAND | wxTOP | wxRIGHT, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

void DetectoratorControlPanel::BindEventHandlers()
{
}

//void DetectoratorControlPanel::OnBtnClick([[maybe_unused]] wxCommandEvent &event)
//{
//    AppMainWindow *parentWin = (AppMainWindow *) parentPanel->GetParent();
//    AppMainWindow *mv = dynamic_cast<AppMainWindow *>(GetParent());
//}
