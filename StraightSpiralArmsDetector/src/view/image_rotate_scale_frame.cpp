#include "image_rotate_scale_frame.hpp"

IRSF::IRSF
(
    IController* controller
) : wxDialog
(
    NULL, wxID_ANY, "Rotate & Scale"
)
{
    this->controller = controller;

    xScaleMult = 10;
    yScaleMult = 10;

    CreateControls();
    SetValuesAndRanges();
    BindEventHandlers();
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

    auto rotateTitle = new wxStaticText(this, -1, wxT("Rotate"));
    SetBoldFont(rotateTitle);
    gridSizer->Add(rotateTitle, gridSizerFlags);

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

    auto rotateOldText = new wxStaticText(this, -1, wxT("Current:"));
    gridSizer->Add(rotateOldText, gridSizerFlags);

    rotateOldValue = new wxStaticText(this, -1, wxT("None"));
    gridSizer->Add(rotateOldValue, gridSizerFlags);

    auto angleSpinNewText = new wxStaticText(this, -1, wxT("Set:"));
    gridSizer->Add(angleSpinNewText, gridSizerFlags);

    angleSpin = new wxSpinCtrl(this);
    gridSizer->Add(angleSpin, gridSizerFlags);

    auto angleSpinText = new wxStaticText(this, -1, wxT("degrees"));
    gridSizer->Add(angleSpinText, gridSizerFlags);

    auto scaleTitle = new wxStaticText(this, -1, wxT("Scale"));
    SetBoldFont(scaleTitle);
    gridSizer->Add(scaleTitle, gridSizerFlags);

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

    auto scaleXOldText = new wxStaticText(this, -1, wxT("Current X:"));
    gridSizer->Add(scaleXOldText, gridSizerFlags);

    scaleXOldValue = new wxStaticText(this, -1, wxT("None"));
    gridSizer->Add(scaleXOldValue, gridSizerFlags);

    auto scaleXNewText = new wxStaticText(this, -1, wxT("Set X:"));
    gridSizer->Add(scaleXNewText, gridSizerFlags);

    scaleXNewSpin = new wxSpinCtrl(this);
    gridSizer->Add(scaleXNewSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, wxT("pixels")), gridSizerFlags);

    auto scaleYOldText = new wxStaticText(this, -1, wxT("Current Y:"));
    gridSizer->Add(scaleYOldText, gridSizerFlags);

    scaleYOldValue = new wxStaticText(this, -1, wxT("None"));
    gridSizer->Add(scaleYOldValue, gridSizerFlags);

    auto scaleYNewText = new wxStaticText(this, -1, wxT("Set Y:"));
    gridSizer->Add(scaleYNewText, gridSizerFlags);

    scaleYNewSpin = new wxSpinCtrl(this);
    gridSizer->Add(scaleYNewSpin, gridSizerFlags);

    gridSizer->Add(new wxStaticText(this, -1, wxT("pixels")), gridSizerFlags);

    AddEmptyCells(4, *gridSizer, gridSizerFlags);

    auto applyChangesBtn = new wxButton(
        this, ID_APPLY_ROTATE_SCALE, wxT("Apply")
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

    scaleXNewSpin->SetRange((rsv.x * xScaleMult), rsv.x * xScaleMult);
    scaleXNewSpin->SetValue(rsv.x);
    scaleXOldValue->SetLabel(std::to_string(rsv.x));

    scaleYNewSpin->SetRange((rsv.y * yScaleMult), rsv.y * yScaleMult);
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
}

void IRSF::AddEmptyCells(unsigned int num_cells, wxGridSizer& grid, wxSizerFlags& flags)
{
    for (unsigned int i = 0; i < num_cells; i++)
    {
        grid.Add(new wxStaticText(this, -1, wxT("")), flags);
    }
}