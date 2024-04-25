#include "image_rotate_scale_frame.hpp"

IRSF::IRSF(
    IController* controller
) : wxDialog(
    NULL, wxID_ANY, _("Rotation and stretching")
)
{
    this->controller = controller;

    xScaleMult = 10;
    yScaleMult = 10;

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
    auto gridSizer = new wxGridSizer(0, 5, wxSize(1, 1));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 5
    ).CenterVertical();

    rotateTitle = new wxStaticText(this, -1, _("Rotation"));
    SetBoldFont(rotateTitle);
    gridSizer->Add(rotateTitle, gridSizerFlags);

    AddEmptyCells(this, 4, *gridSizer, gridSizerFlags);

    rotateOldText = new wxStaticText(this, -1, _("Current value:"));
    gridSizer->Add(rotateOldText, gridSizerFlags);

    rotateOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(rotateOldValue, gridSizerFlags);

    angleSpinNewText = new wxStaticText(this, -1, _("Set value:"));
    gridSizer->Add(angleSpinNewText, gridSizerFlags);

    angleSpin = new wxSpinCtrl(this);
    gridSizer->Add(angleSpin, gridSizerFlags);

    angleSpinText = new wxStaticText(this, -1, _("degrees"));
    gridSizer->Add(angleSpinText, gridSizerFlags);

    scaleTitle = new wxStaticText(this, -1, _("Stretch"));
    SetBoldFont(scaleTitle);
    gridSizer->Add(scaleTitle, gridSizerFlags);

    AddEmptyCells(this, 4, *gridSizer, gridSizerFlags);

    scaleXOldText = new wxStaticText(this, -1, _("Current width:"));
    gridSizer->Add(scaleXOldText, gridSizerFlags);

    scaleXOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(scaleXOldValue, gridSizerFlags);

    scaleXNewText = new wxStaticText(this, -1, _("Set width:"));
    gridSizer->Add(scaleXNewText, gridSizerFlags);

    scaleXNewSpin = new wxSpinCtrl(this);
    gridSizer->Add(scaleXNewSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, _("pixels")), gridSizerFlags);

    scaleYOldText = new wxStaticText(this, -1, _("Current height:"));
    gridSizer->Add(scaleYOldText, gridSizerFlags);

    scaleYOldValue = new wxStaticText(this, -1, "None");
    gridSizer->Add(scaleYOldValue, gridSizerFlags);

    scaleYNewText = new wxStaticText(this, -1, _("Set height:"));
    gridSizer->Add(scaleYNewText, gridSizerFlags);

    scaleYNewSpin = new wxSpinCtrl(this);
    gridSizer->Add(scaleYNewSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, _("pixels")), gridSizerFlags);

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

    angleSpin->SetRange(-180, 180);
    angleSpin->SetValue(rsv.angle);
    rotateOldValue->SetLabel(std::to_string(rsv.angle));

    scaleXNewSpin->SetRange(-(int)(rsv.x * xScaleMult), rsv.x * xScaleMult);
    scaleXNewSpin->SetValue(rsv.x);
    scaleXOldValue->SetLabel(std::to_string(rsv.x));

    scaleYNewSpin->SetRange(-(int)(rsv.y * yScaleMult), rsv.y * yScaleMult);
    scaleYNewSpin->SetValue(rsv.y);
    scaleYOldValue->SetLabel(std::to_string(rsv.y));
}

void IRSF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &IRSF::OnApplyRotateScale, this, ID_APPLY_ROTATE_SCALE);
}

void IRSF::OnApplyRotateScale(wxCommandEvent& WXUNUSED(event))
{
    RotateScaleValues rsv{};

    rsv.angle = angleSpin->GetValue(); 
    rsv.x = scaleXNewSpin->GetValue(); 
    rsv.y = scaleYNewSpin->GetValue();

    CastIRSF->SetRotateScaleValues(rsv);
    SetValuesAndRanges();
}