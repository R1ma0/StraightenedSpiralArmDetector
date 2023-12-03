#include "app_main_window.hpp"

#ifndef CastAMWC
#define CastAMWC dynamic_cast<AppMainWindowController *>(mainController)
#endif
#ifndef CastDCP
#define CastDCP dynamic_cast<DetectoratorControlPanel *>(dcp)
#endif
#ifndef CastBCP
#define CastBCP dynamic_cast<BitmapControlPanel *>(bcp)
#endif

AppMainWindow::AppMainWindow(
    const wxString &title,
    IController *controller
) : wxFrame(
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

    bitmapControlSizer = new wxBoxSizer(wxVERTICAL);
    bitmapControlSizer->Add(bitmap, 1, wxEXPAND | wxALL, FromDIP(10));

    sizerMain = new wxBoxSizer(wxHORIZONTAL);
    sizerMain->Add(bitmapControlSizer, 1, wxEXPAND);

    this->SetSizerAndFit(sizerMain);
}

void AppMainWindow::SetBitmapControlPanel(wxPanel *bcp)
{
    bitmapControlSizer->Add(CastBCP, 0, wxALIGN_LEFT | wxALL, FromDIP(10));
}

void AppMainWindow::SetDetectoratorControlPanel(wxPanel *dcp)
{
    sizerMain->Add(CastDCP, 0, wxEXPAND);
}

void AppMainWindow::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AppMainWindow::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnSaveImg, this, ID_SAVE_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnExit, this, wxID_EXIT);
}

void AppMainWindow::OnExit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

void AppMainWindow::OnLoadImg(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog openFileDialog(
        this, "Select image", "", "", *fileFilters, 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) { return; }

    std::string pathToFile = openFileDialog.GetPath().ToStdString();
    bool isImageNotLoaded = CastAMWC->LoadImage(pathToFile);

    if (isImageNotLoaded)
    {
        wxMessageBox("Failed to open image", "Error", wxOK | wxICON_ERROR);
        return;
    }

    AllowSavingImage(true);
}

void AppMainWindow::OnSaveImg(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog saveFileDialog(
        this,
        "Save image", "", "", 
        *fileFilters, 
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT        
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL) { return; }

    std::string pathToFile = saveFileDialog.GetPath().ToStdString();
    bool isImageSaved = CastAMWC->SaveImage(pathToFile);

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
