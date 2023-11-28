#include "bitmap_control_panel_controller.hpp"

BitmapControlPanelController::BitmapControlPanelController(
    BufferedBitmap *bitmap,
    ProcessedImage *procImage    
)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void BitmapControlPanelController::SetView(wxWindow *view)
{
    selfView = view;
}

void BitmapControlPanelController::OnZoomInBitmap()
{
    bitmap->ZoomInBitmap();
}

void BitmapControlPanelController::OnZoomOutBitmap()
{
    bitmap->ZoomOutBitmap();
}

wxDouble BitmapControlPanelController::GetCurrRotation()
{
    return procImage->GetRotationAngleDegrees();
}

void BitmapControlPanelController::OnRotateBitmap(wxDouble angle)
{
    cv::Mat img = procImage->RotateImage(
        procImage->GetProcessedImage(),
        angle
    );
    bitmap->SetBitmap(wxBitmap(MatToWxImage(img)));
}
