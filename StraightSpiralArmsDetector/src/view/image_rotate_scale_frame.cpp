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
    delete controller;
    delete rotateOldValue;
    delete scaleXOldValue;
    delete scaleYOldValue;
    delete angleSpin;
    delete scaleXNewSpin;
    delete scaleYNewSpin;
    delete rotateTitle;
    delete rotateOldText;
    delete angleSpinNewText;
    delete angleSpinText;
    delete scaleTitle;
    delete scaleXOldText;
    delete scaleXNewText;
    delete scaleYOldText;
    delete scaleYNewText;
    delete applyChangesBtn;
}

void IRSF::SetBoldFont(wxStaticText* text)
{
    wxFont boldFont = text->GetFont();
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    text->SetFont(boldFont);
}

void IRSF::CreateControls()
{
    auto gridSizer = new wxGridSizer(0, 5, wxSize(1, 1));
    auto& gridSizerFlags = wxSizerFlags().Expand().Border(
        wxALL, 10
    ).CenterVertical();

    rotateTitle = new wxStaticText(this, -1, _("Rotation"));
    SetBoldFont(rotateTitle);
    gridSizer->Add(rotateTitle, gridSizerFlags);

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

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

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

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

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

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

void IRSF::AddEmptyCells
(
    unsigned int num_cells, wxGridSizer& grid, wxSizerFlags& flags
)
{
    for (unsigned int i = 0; i < num_cells; i++)
    {
        grid.Add(new wxStaticText(this, -1, ""), flags);
    }
}