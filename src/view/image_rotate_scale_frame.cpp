#include "image_rotate_scale_frame.hpp"

#ifndef IRSF
#define IRSF ImageRotateScaleFrame
#endif
#ifndef IRSFC
#define CastIRSF dynamic_cast<ImageRotateScaleFrameController *>(controller)
#endif

IRSF::IRSF(IController *controller) : wxFrame(NULL, wxID_ANY, "Rotate & Scale")
{
    this->controller = controller;

    xScaleMult = 10;
    yScaleMult = 10;

    CreateControls();
    SetValuesAndRanges();
    BindEventHandlers();
}

void IRSF::SetBoldFont(wxStaticText *text)
{
    wxFont boldFont = text->GetFont();
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);
    text->SetFont(boldFont);
}

void IRSF::CreateControls()
{
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    auto rotateSizerV = new wxBoxSizer(wxVERTICAL);
    auto rotateTitle = new wxStaticText(this, -1, wxT("Rotate:"));
    SetBoldFont(rotateTitle);
    rotateSizerV->Add(rotateTitle, 0, wxLEFT | wxRIGHT, FromDIP(10));
    auto rotateSizerH = new wxBoxSizer(wxHORIZONTAL);
    auto rotateOldText = new wxStaticText(this, -1, wxT("Current:"));
    rotateOldValue = new wxStaticText(this, -1, wxT("None"));
    auto angleSpinNewText = new wxStaticText(this, -1, wxT("Set:"));
    angleSpin = new wxSpinCtrl(this);
    auto angleSpinText = new wxStaticText(this, -1, wxT("degrees"));
    rotateSizerH->Add(rotateOldText, 0, wxALIGN_CENTRE_VERTICAL);
    rotateSizerH->Add(
        rotateOldValue, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(10)
    );
    rotateSizerH->Add(
        angleSpinNewText, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(50)
    );
    rotateSizerH->Add(angleSpin, 0, wxEXPAND);
    rotateSizerH->Add(
        angleSpinText, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(10)
    );
    rotateSizerV->Add(
        rotateSizerH, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, FromDIP(10)
    );

    auto scaleSizerV = new wxBoxSizer(wxVERTICAL);
    auto scaleTitle = new wxStaticText(this, -1, wxT("Scale:"));
    SetBoldFont(scaleTitle);
    scaleSizerV->Add(
        scaleTitle, 0, wxEXPAND | wxLEFT | wxRIGHT, FromDIP(10)
    );
    auto scaleXOldText = new wxStaticText(this, -1, wxT("Current X:"));
    scaleXOldValue = new wxStaticText(this, -1, wxT("None"));
    auto scaleXNewText = new wxStaticText(this, -1, wxT("Set X:"));
    scaleXNewSpin = new wxSpinCtrl(this);
    scaleXNewSpin->SetMinSize(wxSize(200, 35));
    auto scaleXSizerH = new wxBoxSizer(wxHORIZONTAL);
    scaleXSizerH->Add(scaleXOldText, 0, wxALIGN_CENTRE_VERTICAL);
    scaleXSizerH->Add(
        scaleXOldValue, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(10)
    );
    scaleXSizerH->Add(
        scaleXNewText, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(50)
    );
    scaleXSizerH->Add(scaleXNewSpin, 0);
    auto scaleYSizerH = new wxBoxSizer(wxHORIZONTAL);
    auto scaleYOldText = new wxStaticText(this, -1, wxT("Current Y:"));
    scaleYOldValue = new wxStaticText(this, -1, wxT("None"));
    auto scaleYNewText = new wxStaticText(this, -1, wxT("Set Y:"));
    scaleYNewSpin = new wxSpinCtrl(this);
    scaleYNewSpin->SetMinSize(wxSize(200, 35));
    scaleYSizerH->Add(
        scaleYOldText, 0, wxALIGN_CENTRE_VERTICAL
    );
    scaleYSizerH->Add(
        scaleYOldValue, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(10)
    );
    scaleYSizerH->Add(
        scaleYNewText, 0, wxALIGN_CENTRE_VERTICAL | wxLEFT, FromDIP(50)
    );
    scaleYSizerH->Add(scaleYNewSpin, 0);
    scaleSizerV->Add(
        scaleXSizerH, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, FromDIP(10)
    );
    scaleSizerV->Add(
        scaleYSizerH, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, FromDIP(10)
    );

    auto controlsSizer = new wxBoxSizer(wxHORIZONTAL);
    auto applyChangesBtn = new wxButton(
        this, ID_APPLY_ROTATE_SCALE, wxT("Apply")
    );
    controlsSizer->Add(applyChangesBtn, 0, wxTOP | wxBOTTOM, FromDIP(10));

    mainSizer->Add(rotateSizerV, 0, wxEXPAND | wxTOP, FromDIP(10));
    mainSizer->Add(scaleSizerV, 0, wxEXPAND | wxTOP, FromDIP(10));
    mainSizer->Add(controlsSizer, 0, wxALIGN_RIGHT | wxRIGHT, FromDIP(10));

    this->SetSizerAndFit(mainSizer);
}

void IRSF::SetValuesAndRanges()
{
    RotateScaleValues rsv = CastIRSF->GetRotateScaleValues();

    angleSpin->SetRange(-180, 180);
    angleSpin->SetValue(rsv.angle);
    rotateOldValue->SetLabel(std::to_string(rsv.angle));

    scaleXNewSpin->SetRange(-(rsv.x * xScaleMult), rsv.x * xScaleMult);
    scaleXNewSpin->SetValue(rsv.x);
    scaleXOldValue->SetLabel(std::to_string(rsv.x));

    scaleYNewSpin->SetRange(-(rsv.y * yScaleMult), rsv.y * yScaleMult);
    scaleYNewSpin->SetValue(rsv.y);
    scaleYOldValue->SetLabel(std::to_string(rsv.y));
}

void IRSF::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &IRSF::OnApplyRotateScale, this, ID_APPLY_ROTATE_SCALE);
}

void IRSF::OnApplyRotateScale(wxCommandEvent &WXUNUSED(event))
{
    RotateScaleValues rsv;
    rsv.angle = angleSpin->GetValue(); 
    rsv.x = scaleXNewSpin->GetValue(); 
    rsv.y = scaleYNewSpin->GetValue();

    CastIRSF->SetRotateScaleValues(rsv);
}
