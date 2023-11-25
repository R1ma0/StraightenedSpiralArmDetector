#include "app_main_window_controller.hpp"

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

bool AppMainWindowController::LoadImage(const std::string path)
{
    bool uploadStatus = procImage->LoadImage(path);

    if (uploadStatus == false)
    {
        dynamic_cast<AppMainWindow *>(view)->UpdateBitmap(
            GetBitmapImage()        
        );
    }

    return uploadStatus;
}

bool AppMainWindowController::SaveImage(const std::string path)
{
    return procImage->SaveImage(path);
}

void AppMainWindowController::SetView(wxFrame *view)
{
    this->view = view;
}
