#include "app_main_window_controller.hpp"

#ifndef CastAMW
#define CastAMW dynamic_cast<AppMainWindow *>(view)
#endif

AppMainWindowController::AppMainWindowController()
{
    procImage = new ProcessedImage();
}

AppMainWindowController::~AppMainWindowController()
{
    delete procImage;
}

wxBitmap AppMainWindowController::GetBitmapImage()
{
    cv::Mat img = procImage->GetProcessedImage();
    return wxBitmap(MatToWxImage(img));   
}

void AppMainWindowController::OpenRotateScaleFrame(BufferedBitmap *bitmap)
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

void AppMainWindowController::ZoomInBitmap(BufferedBitmap *bitmap)
{
    bitmap->ZoomInBitmap();
}

void AppMainWindowController::ZoomOutBitmap(BufferedBitmap *bitmap)
{
    bitmap->ZoomOutBitmap();
}

bool AppMainWindowController::LoadImage(const std::string path)
{
    bool uploadStatus = procImage->LoadSrcImage(path);

    if (uploadStatus == false)
    {
        CastAMW->UpdateBitmap(GetBitmapImage());
    }

    return uploadStatus;
}

bool AppMainWindowController::SaveImage(const std::string path)
{
    return procImage->SaveImage(path);
}

void AppMainWindowController::SetView(wxWindow *view)
{
    this->view = view;
}

ProcessedImage *AppMainWindowController::GetProcessedImage()
{
    return procImage;
}
