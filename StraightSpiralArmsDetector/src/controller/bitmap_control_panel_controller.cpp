#include "bitmap_control_panel_controller.hpp"

#ifndef BCPC
#define BCPC BitmapControlPanelController
#endif

BCPC::BCPC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void BCPC::SetView(wxWindow *view)
{
    this->view = view;
}

void BCPC::OnZoomInBitmap()
{
    bitmap->ZoomInBitmap();
}

void BCPC::OnZoomOutBitmap()
{
    bitmap->ZoomOutBitmap();
}

wxDouble BCPC::GetCurrRotation()
{
    return procImage->GetRotationAngleDegrees();
}

void BCPC::OpenRotateScaleFrame()
{
    auto rotateScaleController = new ImageRotateScaleFrameController(
        bitmap, 
        procImage
    );
    auto rotateScaleFrame = new ImageRotateScaleFrame(rotateScaleController);
    rotateScaleController->SetView(rotateScaleFrame);
    wxSize bestSize = rotateScaleFrame->GetBestSize();
    rotateScaleFrame->SetSize(bestSize);
    rotateScaleFrame->Show(true);
}
