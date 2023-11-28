#include "bitmap_control_panel.hpp"

BitmapControlPanel::BitmapControlPanel
(
    wxWindow *parent,
    IController *controller
) : wxPanel(parent)
{
    this->controller = controller;
    this->parent = parent;

    CreateControls();
    BindEventHandlers();
}

void BitmapControlPanel::CreateControls()
{
    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    auto zoomInBtn = new wxButton(this, ID_ZOOM_IN, wxT("Zoom +"));
    auto zoomOutBtn = new wxButton(this, ID_ZOOM_OUT, wxT("Zoom -"));
    auto askAngleBtn = new wxButton(this, ID_ANGLE_CHANGE, wxT("Rotate"));

    hSizer->Add(zoomInBtn, 0, wxALIGN_CENTER_VERTICAL);
    hSizer->Add(zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(5));
    hSizer->Add(askAngleBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(15));

    this->SetSizerAndFit(hSizer);
}

void BitmapControlPanel::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(
        wxEVT_BUTTON, 
        &BitmapControlPanel::OnAngleChangeBtn, 
        this, 
        ID_ANGLE_CHANGE
    );
}

void BitmapControlPanel::OnZoomIn(wxCommandEvent &WXUNUSED(event))
{
    dynamic_cast<BCPC *>(controller)->OnZoomInBitmap();
}

void BitmapControlPanel::OnZoomOut(wxCommandEvent &WXUNUSED(event))
{
    dynamic_cast<BCPC *>(controller)->OnZoomOutBitmap();
}

void BitmapControlPanel::OnAngleChangeBtn(wxCommandEvent &WXUNUSED(event))
{
    wxDouble currentAngle = dynamic_cast<BCPC *>(controller)->GetCurrRotation();
    wxDouble newAngle = wxGetNumberFromUser(
        wxT("Change the image rotation angle"),
        wxT("Angle in degrees:"),
        wxT("Rotate image"),
        currentAngle,
        -180, +180,
        this
    );

    if (currentAngle != newAngle)
    {
        dynamic_cast<BCPC *>(controller)->OnRotateBitmap(newAngle);
    }
}
