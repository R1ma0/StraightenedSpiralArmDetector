#include "azsm_control_frame.hpp"

AZSMCF::AZSMCF
(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, "Zhang Suen method settings"
)
{
    this->controller = controller;

    CreateControls();
    BindEventHandlers();
}

void AZSMCF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 2, wxSize(50, 5));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(wxALL, 10).CenterVertical();

    auto binaryThreshValueLabel = new wxStaticText(
        this, -1, wxT("Binary Thresh Value:")
    );
    gridSizer->Add(binaryThreshValueLabel, gridSizerFlags);

    binaryThreshValueSpin = new wxSpinCtrl(this);
    binaryThreshValueSpin->SetRange(0, 255);
    binaryThreshValueSpin->SetValue(125);
    gridSizer->Add(binaryThreshValueSpin, gridSizerFlags);

    auto gaussConstLabel = new wxStaticText(
        this, -1, wxT("Gauss Constant Value:")
    );
    gridSizer->Add(gaussConstLabel, gridSizerFlags);

    gaussConstSpin = new wxSpinCtrl(this);
    gaussConstSpin->SetRange(-20, 20);
    gaussConstSpin->SetValue(0);
    gridSizer->Add(gaussConstSpin, gridSizerFlags);

    auto imgCompressPercentageLabel = new wxStaticText(
        this, -1, wxT("Image Compress Percentage:")
    );
    gridSizer->Add(imgCompressPercentageLabel, gridSizerFlags);

    imgCompressPercentageSpin = new wxSpinCtrl(this);
    imgCompressPercentageSpin->SetRange(1, 99);
    imgCompressPercentageSpin->SetValue(20);
    gridSizer->Add(imgCompressPercentageSpin, gridSizerFlags);

    auto gaussBlockSizeLabel = new wxStaticText(
        this, -1, wxT("Gauss Block Size Value (odd): ")        
    );
    gridSizer->Add(gaussBlockSizeLabel, gridSizerFlags);

    gaussBlockSizeSpin = new wxSpinCtrl(this);
    gaussBlockSizeSpin->SetRange(3, 1001);
    gaussBlockSizeSpin->SetValue(3);
    gridSizer->Add(gaussBlockSizeSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, wxT("")), gridSizerFlags);

    auto computeBtn = new wxButton(
        this, ID_RUN_DETECTORATOR, wxT("Start Processing")
    );
    gridSizer->Add(computeBtn, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMCF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &AZSMCF::OnRunDetectorator, this, ID_RUN_DETECTORATOR);
}

void AZSMCF::OnRunDetectorator(wxCommandEvent& WXUNUSED(event))
{
    CastAZSMFC->RunDetectorator();
}
