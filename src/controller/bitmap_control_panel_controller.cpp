#include "bitmap_control_panel_controller.hpp"

BCPC::BCPC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void BCPC::SetView(wxWindow *view)
{
    selfView = view;
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

void BCPC::OnRotateBitmap(wxDouble angle)
{
    cv::Mat img = procImage->RotateImage(
        procImage->GetProcessedImage(),
        angle
    );
    bitmap->SetBitmap(wxBitmap(MatToWxImage(img)));
}
