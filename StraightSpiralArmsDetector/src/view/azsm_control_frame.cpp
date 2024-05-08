#include "azsm_control_frame.hpp"

AZSMCF::AZSMCF(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, _("Zhang-Suen method settings")
)
{
    this->controller = controller;

    CreateControls();
    BindEventHandlers();
}

AZSMCF::~AZSMCF()
{
    wxDELETE(controller);
}

void AZSMCF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 2, wxSize(50, 5));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    binaryThreshValueLabel = new wxStaticText(
        this, -1, _("Threshold binarisation value:")
    );
    gridSizer->Add(binaryThreshValueLabel, gridSizerFlags);

    binaryThreshValueSpin = new wxSpinCtrl(this, ID_AZSM_BTV_SPIN);
    binaryThreshValueSpin->SetRange(0, 255);
    binaryThreshValueSpin->SetValue(125);
    gridSizer->Add(binaryThreshValueSpin, gridSizerFlags);

    gaussConstLabel = new wxStaticText(
        this, -1, _("Gaussian constant:")
    );
    gridSizer->Add(gaussConstLabel, gridSizerFlags);

    gaussConstSpin = new wxSpinCtrl(this, ID_AZSM_GC_SPIN);
    gaussConstSpin->SetRange(-20, 20);
    gaussConstSpin->SetValue(0);
    gridSizer->Add(gaussConstSpin, gridSizerFlags);

    imgCompressPercentageLabel = new wxStaticText(
        this, -1, _("Image compression percentage:")
    );
    gridSizer->Add(imgCompressPercentageLabel, gridSizerFlags);

    imgCompressPercentageSpin = new wxSpinCtrl(this, ID_AZSM_ICP_SPIN);
    imgCompressPercentageSpin->SetRange(1, 99);
    imgCompressPercentageSpin->SetValue(20);
    gridSizer->Add(imgCompressPercentageSpin, gridSizerFlags);

    gaussBlockSizeLabel = new wxStaticText(
        this, -1, _("Gaussian block size value (odd):")        
    );
    gridSizer->Add(gaussBlockSizeLabel, gridSizerFlags);

    gaussBlockSizeSpin = new wxSpinCtrl(this, ID_AZSM_GBS_SPIN);
    gaussBlockSizeSpin->SetRange(3, 1001);
    gaussBlockSizeSpin->SetValue(3);
    gridSizer->Add(gaussBlockSizeSpin, gridSizerFlags);

    enableLivePreviewCB = new wxCheckBox(
        this, 
        ID_ENABLE_LIVE_PREVIEW, 
        _("Live Preview")
    );
    gridSizer->Add(enableLivePreviewCB, gridSizerFlags);
    enableLivePreviewCB->Hide();

    computeBtn = new wxButton(
        this, ID_RUN_DETECTORATOR, _("Process")
    );
    gridSizer->Add(computeBtn, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void AZSMCF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &AZSMCF::OnRunDetectorator, this, ID_RUN_DETECTORATOR);
    Bind(wxEVT_SPINCTRL, &AZSMCF::OnSetGaussBlockSize, this, ID_AZSM_GBS_SPIN);
    Bind(wxEVT_SPINCTRL, &AZSMCF::OnSpinValuesChange, this, ID_AZSM_BTV_SPIN);
    Bind(wxEVT_SPINCTRL, &AZSMCF::OnSpinValuesChange, this, ID_AZSM_ICP_SPIN);
    Bind(wxEVT_SPINCTRL, &AZSMCF::OnSpinValuesChange, this, ID_AZSM_GC_SPIN);
    Bind(
        wxEVT_CHECKBOX,
        &AZSMCF::OnEnableLivePreview,
        this,
        ID_ENABLE_LIVE_PREVIEW
    );
}

void AZSMCF::OnSetGaussBlockSize(wxCommandEvent& WXUNUSED(event))
{
    gaussBlockSizeSpin->SetValue(
        CheckOddValue(gaussBlockSizeSpin->GetValue(), &gbsOldValue)
    );

    if (isEnableLivePreview)
    {
        CastAZSMFC->RunDetectorator();
    }
}

void AZSMCF::OnRunDetectorator(wxCommandEvent& WXUNUSED(event))
{
    CastAZSMFC->RunDetectorator();
}

void AZSMCF::SetEnableComponents(bool state)
{
    computeBtn->Enable(state);
    binaryThreshValueSpin->Enable(state);
    gaussConstSpin->Enable(state);
    imgCompressPercentageSpin->Enable(state);
    gaussBlockSizeSpin->Enable(state);
    binaryThreshValueLabel->Enable(state);
    gaussConstLabel->Enable(state);
    imgCompressPercentageLabel->Enable(state);
    gaussBlockSizeLabel->Enable(state);
    enableLivePreviewCB->Enable(state);
}

void AZSMCF::OnEnableLivePreview(wxCommandEvent& WXUNUSED(event))
{
    isEnableLivePreview = enableLivePreviewCB->IsChecked() ? true : false;
}

void AZSMCF::OnSpinValuesChange(wxSpinEvent& WXUNUSED(event))
{
    if (isEnableLivePreview)
    {
        CastAZSMFC->RunDetectorator();
    }
}