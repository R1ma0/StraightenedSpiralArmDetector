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
    cv::Mat img = procImage->GetProcessedImage();
    cv::Size currentSize = procImage->GetImageSize();
    
    if (currentSize.width != rsv.x || currentSize.height != rsv.y)
    {
        cv::resize(img, img, cv::Size(rsv.x, rsv.y), cv::INTER_LINEAR);
    }

    if (rsv.angle != procImage->GetRotationAngleDegrees())
    {
        img = procImage->RotateImage(img, rsv.angle);
    }

    procImage->SetProcessedImage(img);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(&img)));
}

RotateScaleValues IRSFC::GetRotateScaleValues()
{
    RotateScaleValues rsv{};

    rsv.angle = procImage->GetRotationAngleDegrees();
    rsv.x = procImage->GetImageSize().width;
    rsv.y = procImage->GetImageSize().height;

    return rsv;
}
