#include "bitmap_control_panel.hpp"

BitmapControlPanel::BitmapControlPanel
(
    wxFrame *parentFrame, 
    BufferedBitmap *bitmap, 
    ProcessedImage *procImage
) : wxPanel(parentFrame)
{
    this->bitmap = bitmap;
    this->procImage = procImage;

    CreateControls();
    BindEventHandlers();
}

void BitmapControlPanel::CreateControls()
{
    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    auto zoomInBtn = new wxButton(this, ID_ZOOM_IN, wxT("Zoom +"));
    auto zoomOutBtn = new wxButton(this, ID_ZOOM_OUT, wxT("Zoom -"));
    auto askAngleBtn = new wxButton(this, ID_ANGLE_CHANGE, wxT("Rotate"));

    hSizer->Add(
        zoomInBtn, 0, wxALIGN_CENTER_VERTICAL
    );
    hSizer->Add(
        zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(5)        
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
    Bind(
        wxEVT_BUTTON, 
        &BitmapControlPanel::OnAngleChangeBtn, 
        this, 
        ID_ANGLE_CHANGE
    );
}

void BitmapControlPanel::OnZoomIn([[maybe_unused]] wxCommandEvent &event)
{
    bitmap->ZoomInBitmap();
}

void BitmapControlPanel::OnZoomOut([[maybe_unused]] wxCommandEvent &event)
{
    bitmap->ZoomOutBitmap();
}

void BitmapControlPanel::OnAngleChangeBtn
(
    [[maybe_unused]] wxCommandEvent &event
)
{
    wxDouble currentAngle = procImage->GetRotationAngleDegrees();
    wxDouble newAngle = wxGetNumberFromUser(
        wxT("Change the image rotation angle"),
        wxT("Angle in degrees:"),
        wxT("Rotate image"),
        currentAngle,
        -360, +360,
        this
    );
    
    if (currentAngle!= newAngle)
    {
        cv::Mat img = procImage->RotateImage(
            procImage->GetProcessedImage(),
            newAngle
        );
        bitmap->SetBitmap(wxBitmap(MatToWxImage(img)));
    }
}
