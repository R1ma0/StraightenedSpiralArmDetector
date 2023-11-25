#include "app_main_window.hpp"

AppMainWindow::AppMainWindow(
    const wxString &title,
    IController *controller
) : wxFrame
(
    nullptr, wxID_ANY, title
)
{
    mainController = controller;

    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    fileFilters = new wxString(
        "Images (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg"
    );

    CreateControls();
    BindEventHandlers();
    AllowSavingImage(false);
}

AppMainWindow::~AppMainWindow() 
{
    delete bitmap;
    delete saveImg;
}

void AppMainWindow::CreateControls()
{
    auto menuFile = new wxMenu();
    auto loadImg = new wxMenuItem(
        menuFile, ID_LOAD_IMG, wxT("Load Image\tCtrl-O"), 
        wxT("Opening and loading an image for processing")
    );
    saveImg = new wxMenuItem(
        menuFile, ID_SAVE_IMG, wxT("Save Image\tCtrl-S"),        
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

    //auto bcp = new BitmapControlPanel(this, bitmap, procImage);
    auto sizerLeft = new wxBoxSizer(wxVERTICAL);
    sizerLeft->Add(bitmap, 1, wxEXPAND | wxALL, FromDIP(10));
    //sizerLeft->Add(bcp, 0, wxALIGN_LEFT | wxALL, FromDIP(10));

    //auto dcp = new DetectoratorControlPanel(this, bitmap, procImage);
    auto sizerMain = new wxBoxSizer(wxHORIZONTAL);
    sizerMain->Add(sizerLeft, 1, wxEXPAND);
    //sizerMain->Add(dcp, 0, wxEXPAND);

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
        *fileFilters, 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) { return; }

    std::string pathToFile = openFileDialog.GetPath().ToStdString();
    bool isImageNotLoaded = dynamic_cast<
        AppMainWindowController *
    >(mainController)->LoadImage(pathToFile);

    if (isImageNotLoaded)
    {
        wxMessageBox("Failed to open image", "Error", wxOK | wxICON_ERROR);
        return;
    }

    AllowSavingImage(true);
}

void AppMainWindow::OnSaveImg([[maybe_unused]] wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(
        this,
        "Save image", "", "", 
        *fileFilters, 
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT        
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL) { return; }

    std::string pathToFile = saveFileDialog.GetPath().ToStdString();
    bool isImageSaved = dynamic_cast<
        AppMainWindowController *    
    >(mainController)->SaveImage(pathToFile);

    if (!isImageSaved)
    {
        wxMessageBox("Failed to save image", "Error", wxOK | wxICON_ERROR);
        return;
    }
}

void AppMainWindow::AllowSavingImage(bool state)
{
    saveImg->Enable(state);
}

void AppMainWindow::UpdateBitmap(wxBitmap bmp)
{
    bitmap->SetBitmap(bmp);
    this->Layout();
}
