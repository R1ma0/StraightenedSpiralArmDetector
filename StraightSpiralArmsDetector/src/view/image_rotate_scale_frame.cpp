#include "image_rotate_scale_frame.hpp"

IRSF::IRSF(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, _("Rotation and stretching")
)
{
    this->controller = controller;

    baseImageSize = CastIRSF->GetBaseImageSize();

    CreateControls();
    SetValuesAndRanges();
    BindEventHandlers();
}

IRSF::~IRSF()
{
    wxDELETE(controller);
}

void IRSF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 6, wxSize(1, 1));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    rotateTitle = new wxStaticText(this, -1, _("Rotation"));
    SetBoldFont(rotateTitle);
    gridSizer->Add(rotateTitle, gridSizerFlags);

    AddEmptyCells(this, 5, *gridSizer, gridSizerFlags);

    rotateOldText = new wxStaticText(this, -1, _("Current value:"));
    gridSizer->Add(rotateOldText, gridSizerFlags);

    rotateOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(rotateOldValue, gridSizerFlags);

    angleSpinNewText = new wxStaticText(this, -1, _("Set value:"));
    gridSizer->Add(angleSpinNewText, gridSizerFlags);

    angleSpin = new wxSpinCtrl(this, ID_ON_ANGLE_CHANGE);
    gridSizer->Add(angleSpin, gridSizerFlags);

    angleSlider = new wxSlider(this, ID_ANGLE_SLIDER, 0, -1, 1);
    gridSizer->Add(angleSlider, gridSizerFlags);

    angleSpinText = new wxStaticText(this, -1, _("°"));
    gridSizer->Add(angleSpinText, gridSizerFlags);

    scaleTitle = new wxStaticText(this, -1, _("Stretch"));
    SetBoldFont(scaleTitle);
    gridSizer->Add(scaleTitle, gridSizerFlags);

    AddEmptyCells(this, 5, *gridSizer, gridSizerFlags);

    scaleXOldText = new wxStaticText(this, -1, _("Current width:"));
    gridSizer->Add(scaleXOldText, gridSizerFlags);

    scaleXOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(scaleXOldValue, gridSizerFlags);

    scaleXNewText = new wxStaticText(this, -1, _("Set width:"));
    gridSizer->Add(scaleXNewText, gridSizerFlags);

    scaleXNewSpin = new wxSpinCtrl(this, ID_ON_NEW_X_SCALE_CHANGE);
    gridSizer->Add(scaleXNewSpin, gridSizerFlags);

    scaleXNewSlider = new wxSlider(this, ID_NEW_X_SLIDER, 0, -1, 1);
    gridSizer->Add(scaleXNewSlider, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, _("px")), gridSizerFlags);

    scaleYOldText = new wxStaticText(this, -1, _("Current height:"));
    gridSizer->Add(scaleYOldText, gridSizerFlags);

    scaleYOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(scaleYOldValue, gridSizerFlags);

    scaleYNewText = new wxStaticText(this, -1, _("Set height:"));
    gridSizer->Add(scaleYNewText, gridSizerFlags);

    scaleYNewSpin = new wxSpinCtrl(this, ID_ON_NEW_Y_SCALE_CHANGE);
    gridSizer->Add(scaleYNewSpin, gridSizerFlags);

    scaleYNewSlider = new wxSlider(this, ID_NEW_Y_SLIDER, 0, -1, 1);
    gridSizer->Add(scaleYNewSlider, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, _("px")), gridSizerFlags);

    enableLivePreviewCB = new wxCheckBox(
        this, 
        ID_ENABLE_LIVE_PREVIEW, 
        _("Live Preview")
    );
    gridSizer->Add(enableLivePreviewCB, gridSizerFlags);

    AddEmptyCells(this, 4, *gridSizer, gridSizerFlags);

    applyChangesBtn = new wxButton(
        this, ID_APPLY_ROTATE_SCALE, _("Apply")
    );
    gridSizer->Add(applyChangesBtn, gridSizerFlags);

    this->SetSizer(gridSizer);
    gridSizer->SetSizeHints(this);
}

void IRSF::SetValuesAndRanges()
{
    RotateScaleValues rsv = CastIRSF->GetRotateScaleValues();

    angleSpin->SetRange(ANGLE_MIN_RANGE, ANGLE_MAX_RANGE);
    angleSpin->SetValue(rsv.angle);
    angleSlider->SetRange(ANGLE_MIN_RANGE, ANGLE_MAX_RANGE);
    angleSlider->SetValue(rsv.angle);
    rotateOldValue->SetLabel(std::to_string(rsv.angle));

    scaleXNewSpin->SetRange(1, baseImageSize.GetWidth() * X_SCALE_MULT);
    scaleXNewSpin->SetValue(rsv.x);
    scaleXNewSlider->SetRange(1, baseImageSize.GetWidth() * X_SCALE_MULT);
    scaleXNewSlider->SetValue(rsv.x);
    scaleXOldValue->SetLabel(std::to_string(rsv.x));

    scaleYNewSpin->SetRange(1, baseImageSize.GetHeight() * Y_SCALE_MULT);
    scaleYNewSpin->SetValue(rsv.y);
    scaleYNewSlider->SetRange(1, baseImageSize.GetHeight() * Y_SCALE_MULT);
    scaleYNewSlider->SetValue(rsv.y);
    scaleYOldValue->SetLabel(std::to_string(rsv.y));
}

void IRSF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &IRSF::OnApplyRotateScale, this, ID_APPLY_ROTATE_SCALE);
    Bind(
        wxEVT_CHECKBOX, 
        &IRSF::OnEnableLivePreview, 
        this, 
        ID_ENABLE_LIVE_PREVIEW
    );
    Bind(wxEVT_SPINCTRL, &IRSF::OnAngleSpinChange, this, ID_ON_ANGLE_CHANGE);
    Bind(
        wxEVT_SPINCTRL, 
        &IRSF::OnNewScaleXSpinChange, 
        this, 
        ID_ON_NEW_X_SCALE_CHANGE
    );
    Bind(
        wxEVT_SPINCTRL,
        &IRSF::OnNewScaleYSpinChange,
        this,
        ID_ON_NEW_Y_SCALE_CHANGE
    );
    Bind(wxEVT_SLIDER, &IRSF::OnAngleSliderChange, this, ID_ANGLE_SLIDER);
    Bind(wxEVT_SLIDER, &IRSF::OnNewScaleXSliderChange, this, ID_NEW_X_SLIDER);
    Bind(wxEVT_SLIDER, &IRSF::OnNewScaleYSliderChange, this, ID_NEW_Y_SLIDER);
}

void IRSF::PerformProcessing()
{
    RotateScaleValues rsv{};

    rsv.angle = angleSpin->GetValue();
    rsv.x = scaleXNewSpin->GetValue();
    rsv.y = scaleYNewSpin->GetValue();

    CastIRSF->SetRotateScaleValues(rsv);
    SetValuesAndRanges();
}

void IRSF::IfEnableLivePreviewPerformProcessing()
{
    if (isEnabledLivePreview)
    {
        PerformProcessing();
    }
}

void IRSF::OnEnableLivePreview(wxCommandEvent& WXUNUSED(event))
{
    isEnabledLivePreview = enableLivePreviewCB->IsChecked() ? true : false;
}

void IRSF::OnApplyRotateScale(wxCommandEvent& WXUNUSED(event))
{
    PerformProcessing();
}

void IRSF::OnAngleSpinChange(wxSpinEvent& WXUNUSED(event))
{
    UpdateValue(angleSpin, angleSlider);
    IfEnableLivePreviewPerformProcessing();
}

void IRSF::OnAngleSliderChange(wxCommandEvent& WXUNUSED(event))
{
    UpdateValue(angleSlider, angleSpin);
    IfEnableLivePreviewPerformProcessing();
}

void IRSF::OnNewScaleXSpinChange(wxSpinEvent& WXUNUSED(event))
{
    UpdateValue(scaleXNewSpin, scaleXNewSlider);
    IfEnableLivePreviewPerformProcessing();
}

void IRSF::OnNewScaleXSliderChange(wxCommandEvent& WXUNUSED(event))
{
    UpdateValue(scaleXNewSlider, scaleXNewSpin);
    IfEnableLivePreviewPerformProcessing();
}

void IRSF::OnNewScaleYSpinChange(wxSpinEvent& WXUNUSED(event))
{
    UpdateValue(scaleYNewSpin, scaleYNewSlider);
    IfEnableLivePreviewPerformProcessing();
}

void IRSF::OnNewScaleYSliderChange(wxCommandEvent& WXUNUSED(event))
{
    UpdateValue(scaleYNewSlider, scaleYNewSpin);
    IfEnableLivePreviewPerformProcessing();
}

template <typename T, typename F>
void IRSF::UpdateValue(T* from, F* to)
{
    to->SetValue(from->GetValue());
}