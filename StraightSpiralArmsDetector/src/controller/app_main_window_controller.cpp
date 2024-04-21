#include "app_main_window_controller.hpp"

AMWC::AMWC(Configurator* configurator)
{
    procImage = new ProcessedImage();
    this->configurator = configurator;

    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);
}

AMWC::~AMWC()
{
    wxDELETE(procImage);
}

wxBitmap AMWC::GetBitmapImage()
{
    cv::Mat img = procImage->GetProcessedImage();
    return wxBitmap(MatToWxImage(&img));
}

void AMWC::InitModalDialog(wxDialog* dialog, wxSize size)
{
    wxSize dialogSize;

    if (size == wxDefaultSize)
    {
        dialogSize = dialog->GetBestSize();
    }
    else
    {
        dialogSize = size;
    }
    
    dialog->SetSize(dialogSize);
    dialog->Center();
    dialog->ShowModal();
    wxDELETE(dialog);
}

void AppMainWindowController::OpenRotateScaleFrame(BufferedBitmap* bitmap)
{
    auto rotateScaleController = new ImageRotateScaleFrameController(
        bitmap,
        procImage
    );
    auto rotateScaleFrame = new ImageRotateScaleFrame(rotateScaleController);
    rotateScaleController->SetView(rotateScaleFrame);
    InitModalDialog(rotateScaleFrame);
}

void AMWC::OpenAZSMethodFrame(BufferedBitmap* bitmap)
{
    auto azsmController = new AZSMFrameController(bitmap, procImage);
    auto azsmFrame = new AZSMControlFrame(azsmController);
    azsmController->SetView(azsmFrame);
    InitModalDialog(azsmFrame);
}

void AMWC::OpenAZSMMultipleProcessingFrame()
{
    auto azsmmpController = new AZSMMultipleProcessingFrameController();
    auto azsmmpFrame = new AZSMMultipleProcessingFrame(azsmmpController);
    azsmmpController->SetView(azsmmpFrame);
    InitModalDialog(azsmmpFrame);
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
    wxFileDialog* openFileDialog = new wxFileDialog(
        CastAMW, 
        _("Image selection"), 
        "", 
        "", 
        cts::FILE_FILTERS,
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (openFileDialog->ShowModal() == wxID_CANCEL) 
    { 
        wxDELETE(openFileDialog);
        return true; 
    }

    std::string* pathToFile = new std::string(
        openFileDialog->GetPath().ToStdString()
    );
    bool uploadStatus = procImage->LoadSrcImage(pathToFile);

    if (uploadStatus == false)
    {
        CastAMW->UpdateBitmap(GetBitmapImage());
    }

    wxDELETE(pathToFile);
    wxDELETE(openFileDialog);

    return uploadStatus;
}

bool AMWC::SaveImage()
{
    wxFileDialog* saveFileDialog = new wxFileDialog(
        CastAMW,
        _("Image saving"),
        "",
        "",
        cts::FILE_FILTERS,
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if (saveFileDialog->ShowModal() == wxID_CANCEL) 
    { 
        return true;
    }

    std::string pathToFile = saveFileDialog->GetPath().ToStdString();

    wxDELETE(saveFileDialog);

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