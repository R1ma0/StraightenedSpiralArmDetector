#include "bitmap_control_panel.hpp"

BitmapControlPanel::BitmapControlPanel(
    wxFrame *parentWindow, wxPanel *parentWinPanel        
) : wxPanel(parentWindow)
{
    parentPanel = parentWinPanel;

    CreateControls();
    BindEventHandlers();
}

BitmapControlPanel::~BitmapControlPanel() {}

void BitmapControlPanel::CreateControls()
{
    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    auto zoomInBtn = new wxButton(this, ID_ZOOM_IN, wxT("Zoom +"));
    auto zoomOutBtn = new wxButton(this, ID_ZOOM_OUT, wxT("Zoom -"));
    auto askAngleBtn = new wxButton(this, ID_ANGLE_CHANGE, wxT("Rotate"));

    hSizer->Add(
        zoomInBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, FromDIP(5)
    );
    hSizer->Add(
        zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL, FromDIP(5)        
    );
    hSizer->Add(
        askAngleBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(15)
    );

    this->SetSizerAndFit(hSizer);
}

void BitmapControlPanel::BindEventHandlers()
{
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnZoomOut, this, ID_ZOOM_OUT);
    Bind(wxEVT_BUTTON, &BitmapControlPanel::OnAngleChangeBtn, this, ID_ANGLE_CHANGE);
}

void BitmapControlPanel::OnZoomIn([[maybe_unused]] wxCommandEvent &event)
{
    AppMainWindow *parentWin = (AppMainWindow *)parentPanel->GetParent();
    parentWin->BitmapZoomIn();
}

void BitmapControlPanel::OnZoomOut([[maybe_unused]] wxCommandEvent &event)
{
    AppMainWindow *parentWin = (AppMainWindow *)parentPanel->GetParent();
    parentWin->BitmapZoomOut();
}

void BitmapControlPanel::OnAngleChangeBtn(
    [[maybe_unused]] wxCommandEvent &event
)
{
    AppMainWindow *parentWin = (AppMainWindow *)parentPanel->GetParent();

    long degrees = (180 * parentWin->GetBitmapRotationRadians()) / M_PI;
    
    degrees = wxGetNumberFromUser(
        wxT("Change the image rotation angle"),
        wxT("Angle in degrees:"),
        wxT("Rotate image"),
        degrees,
        0, +360,
        this
    );
    
    parentWin->BitmapRotate(degrees);
}
