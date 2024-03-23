#include "azsm_control_frame.hpp"

AZSMCF::AZSMCF
(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, _("Zhang-Suen method settings")
)
{
    this->controller = controller;

    CreateControls();
    BindEventHandlers();
}

void AZSMCF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 2, wxSize(50, 5));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    auto binaryThreshValueLabel = new wxStaticText(
        this, -1, _("Threshold binarisation value:")
    );
    gridSizer->Add(binaryThreshValueLabel, gridSizerFlags);

    binaryThreshValueSpin = new wxSpinCtrl(this);
    binaryThreshValueSpin->SetRange(0, 255);
    binaryThreshValueSpin->SetValue(125);
    gridSizer->Add(binaryThreshValueSpin, gridSizerFlags);

    auto gaussConstLabel = new wxStaticText(
        this, -1, _("Gaussian constant:")
    );
    gridSizer->Add(gaussConstLabel, gridSizerFlags);

    gaussConstSpin = new wxSpinCtrl(this);
    gaussConstSpin->SetRange(-20, 20);
    gaussConstSpin->SetValue(0);
    gridSizer->Add(gaussConstSpin, gridSizerFlags);

    auto imgCompressPercentageLabel = new wxStaticText(
        this, -1, _("Image compression percentage:")
    );
    gridSizer->Add(imgCompressPercentageLabel, gridSizerFlags);

    imgCompressPercentageSpin = new wxSpinCtrl(this);
    imgCompressPercentageSpin->SetRange(1, 99);
    imgCompressPercentageSpin->SetValue(20);
    gridSizer->Add(imgCompressPercentageSpin, gridSizerFlags);

    auto gaussBlockSizeLabel = new wxStaticText(
        this, -1, _("Gaussian block size value (odd): ")        
    );
    gridSizer->Add(gaussBlockSizeLabel, gridSizerFlags);

    gaussBlockSizeSpin = new wxSpinCtrl(this, ID_GBS_SPIN);
    gaussBlockSizeSpin->SetRange(CastAZSMFC->GBS_SPIN_DEFAULT_VALUE, 1001);
    gaussBlockSizeSpin->SetValue(CastAZSMFC->GBS_SPIN_DEFAULT_VALUE);
    gridSizer->Add(gaussBlockSizeSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, wxT("")), gridSizerFlags);

    auto computeBtn = new wxButton(
        this, ID_RUN_DETECTORATOR, _("Process")
    );
    gridSizer->Add(computeBtn, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMCF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &AZSMCF::OnRunDetectorator, this, ID_RUN_DETECTORATOR);
    Bind(wxEVT_SPINCTRL, &AZSMCF::OnSetGaussBlockSize, this, ID_GBS_SPIN);
}

void AZSMCF::OnSetGaussBlockSize(wxCommandEvent& WXUNUSED(event))
{
    gaussBlockSizeSpin->SetValue(
        CastAZSMFC->CheckGBSValue(gaussBlockSizeSpin->GetValue())
    );
}

void AZSMCF::OnRunDetectorator(wxCommandEvent& WXUNUSED(event))
{
    CastAZSMFC->RunDetectorator();
}
