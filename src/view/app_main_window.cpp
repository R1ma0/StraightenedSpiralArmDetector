#include "app_main_window.hpp"

AppMainWindow::AppMainWindow(const wxString &title) : wxFrame(
    nullptr, wxID_ANY, title
)
{
    mainPanel = new wxPanel(this, wxID_ANY);
    procImage = new ProcessedImage();

    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    CreateControls();
    BindEventHandlers();
    AllowSavingImage(false);
}

AppMainWindow::~AppMainWindow() 
{
    delete bitmap;
}

wxPanel *AppMainWindow::GetMainPanel()
{
    return mainPanel;
}

void AppMainWindow::CreateControls()
{
    auto menuFile = new wxMenu();
    auto loadImg = new wxMenuItem(
        menuFile, ID_LOAD_IMG, wxT("Load image\tCtrl-O"), 
        wxT("Opening and loading an image for processing")
    );
    saveImg = new wxMenuItem(
        menuFile, ID_SAVE_IMG, wxT("Save image\tCtrl-S"),        
        wxT("Saving processed image")
    );
    menuFile->Append(loadImg);
    menuFile->Append(saveImg);
    menuFile->Append(wxID_EXIT);

    auto menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("File"));
    SetMenuBar(menuBar);
    
    CreateStatusBar();

    bitmap = new BufferedBitmap(
        this, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, 
        FromDIP(wxSize(1, 1)), 0
    );

    auto bcp = new BitmapControlPanel(this, GetMainPanel());
    auto sizerLeft = new wxBoxSizer(wxVERTICAL);
    sizerLeft->Add(bitmap, 1, wxEXPAND | wxALL, FromDIP(10));
    sizerLeft->Add(bcp, 0, wxALIGN_LEFT | wxALL, FromDIP(10));

    auto dcp = new DetectoratorControlPanel(this, GetMainPanel());
    auto sizerMain = new wxBoxSizer(wxHORIZONTAL);
    sizerMain->Add(sizerLeft, 1, wxEXPAND);
    sizerMain->Add(dcp, 0, wxEXPAND);

    this->SetSizerAndFit(sizerMain);
}

void AppMainWindow::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AppMainWindow::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnSaveImg, this, ID_SAVE_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnExit, this, wxID_EXIT);
}

void AppMainWindow::OnExit([[maybe_unused]] wxCommandEvent &event)
{
    Close(true);
}

void AppMainWindow::OnLoadImg([[maybe_unused]] wxCommandEvent &event)
{
    wxFileDialog openFileDialog(
        this, 
        "Select image", "", "", 
        ("PNG & JPG files (*.png;*.jpg)|*.png;*.jpg"), 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) { return; }

    bool isImageNotLoaded = procImage->LoadImage(
        openFileDialog.GetPath().ToStdString()
    );

    if (isImageNotLoaded)
    {
        wxMessageBox("Failed to open image", "Error", wxOK | wxICON_ERROR);
        return;
    }

    UpdateBitmapImage();
    AllowSavingImage(true);
}

void AppMainWindow::OnSaveImg([[maybe_unused]] wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(
        this,
        "Save image", "", "",
        ("PNG & JPG files (*.png;*.jpg)|*.png;*.jpg"), 
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT        
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL) { return; }
}

void AppMainWindow::AllowSavingImage(bool state)
{
    saveImg->Enable(state);
}

void AppMainWindow::UpdateBitmapImage()
{
    cv::Mat img = procImage->GetProcessedImage();
    bitmap->SetBitmap(wxBitmap(MatToWxImage(img)));
    this->Layout();
}

wxImage AppMainWindow::MatToWxImage(cv::Mat img)
{
    if (img.channels() == 1) { cv::cvtColor(img, img, cv::COLOR_GRAY2RGB); }
    else if (img.channels() == 4) { cv::cvtColor(img, img, cv::COLOR_BGRA2RGB); }
    else { cv::cvtColor(img, img, cv::COLOR_BGR2RGB); }

    long imageSize = img.rows * img.cols * img.channels();

    wxImage image(img.cols, img.rows, (unsigned char *)malloc(imageSize), false);
    unsigned char *matData = img.data;
    unsigned char *wxData = image.GetData();

    for (long i = 0; i < imageSize; i++) { wxData[i] = matData[i]; }

    return image;
}
