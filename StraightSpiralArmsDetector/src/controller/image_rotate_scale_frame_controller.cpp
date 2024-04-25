#include "image_rotate_scale_frame_controller.hpp"

IRSFC::IRSFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void IRSFC::SetView(wxWindow* view)
{
    this->view = view;
}

void IRSFC::SetRotateScaleValues(RotateScaleValues rsv)
{
    cv::Size currentSize = procImage->GetImageSize();
    
    if (currentSize.width != rsv.x || currentSize.height != rsv.y)
    {
        procImage->ResizeImage(rsv.x, rsv.y);
    }

    if (rsv.angle != procImage->GetRotationAngleDegrees())
    {
        procImage->RotateImage(rsv.angle);
    }

    cv::Mat image = procImage->GetProcessedImage();
    bitmap->SetBitmap(wxBitmap(MatToWxImage(&image)));
}

RotateScaleValues IRSFC::GetRotateScaleValues()
{
    RotateScaleValues rsv{};

    rsv.angle = procImage->GetRotationAngleDegrees();
    rsv.x = procImage->GetImageSize().width;
    rsv.y = procImage->GetImageSize().height;

    return rsv;
}
