#include "app_main_window_controller.hpp"

AMWC::AMWC()
{
    procImage = new ProcessedImage();

    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    fileFilters = new wxString(
        "Images (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg"
    );
}

AMWC::~AMWC()
{
    delete procImage;
}

wxBitmap AMWC::GetBitmapImage()
{
    cv::Mat img = procImage->GetProcessedImage();
    return wxBitmap(MatToWxImage(img));   
}

void AMWC::OpenRotateScaleFrame(BufferedBitmap* bitmap)
{
    auto rotateScaleController = new ImageRotateScaleFrameController(
        bitmap,
        procImage
    );
    auto rotateScaleFrame = new ImageRotateScaleFrame(rotateScaleController);
    rotateScaleController->SetView(rotateScaleFrame);
    wxSize bestSize = rotateScaleFrame->GetBestSize();
    rotateScaleFrame->SetSize(bestSize);
    rotateScaleFrame->ShowModal();
    rotateScaleFrame->Destroy();
}

void AMWC::OpenAZSMethodFrame(BufferedBitmap* bitmap)
{
    auto azsmController = new AZSMFrameController(bitmap, procImage);
    auto azsmFrame = new AZSMControlFrame(azsmController);
    azsmController->SetView(azsmFrame);
    wxSize bestSize = azsmFrame->GetBestSize();
    azsmFrame->SetSize(bestSize);
    azsmFrame->ShowModal();
    azsmFrame->Destroy();
}

void AMWC::ZoomInBitmap(BufferedBitmap* bitmap)
{
    bitmap->ZoomInBitmap();
}

void AMWC::ZoomOutBitmap(BufferedBitmap* bitmap)
{
    bitmap->ZoomOutBitmap();
}

bool AMWC::LoadImage()
{
    wxFileDialog openFileDialog(
        CastAMW, 
        "Select image", 
        "", 
        "", 
        *fileFilters,
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (openFileDialog.ShowModal() == wxID_CANCEL) 
    { 
        return true; 
    }

    std::string pathToFile = openFileDialog.GetPath().ToStdString();
    bool uploadStatus = procImage->LoadSrcImage(pathToFile);

    if (uploadStatus == false)
    {
        CastAMW->UpdateBitmap(GetBitmapImage());
    }

    return uploadStatus;
}

bool AMWC::SaveImage()
{
    wxFileDialog saveFileDialog(
        CastAMW,
        "Save image",
        "",
        "",
        *fileFilters,
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL) 
    { 
        return true;
    }

    std::string pathToFile = saveFileDialog.GetPath().ToStdString();

    return procImage->SaveImage(pathToFile);
}

void AMWC::SetView(wxWindow* view)
{
    this->view = view;
}

ProcessedImage* AMWC::GetProcessedImage()
{
    return procImage;
}