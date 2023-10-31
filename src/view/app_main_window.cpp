#include "app_main_window.hpp"

AppMainWindow::AppMainWindow(const wxString &title) : wxFrame(
    nullptr, wxID_ANY, title
)
{
    mainPanel = new wxPanel(this, wxID_ANY);

    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    CreateControls();
    BindEventHandlers();
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
    menuFile->Append(loadImg);
    menuFile->Append(wxID_EXIT);

    auto menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("File"));
    SetMenuBar(menuBar);
    
    CreateStatusBar();

    bitmap = new BufferedBitmap(
        this, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, 
        FromDIP(wxSize(500, 200)), 0
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

    if (!loadedImg.LoadFile(openFileDialog.GetPath()))
    {
        wxMessageBox("Failed to open image", "Error", wxOK | wxICON_ERROR);
        return;
    }

    UpdateBitmapImage(loadedImg);
}

void AppMainWindow::UpdateBitmapImage(const wxImage &img)
{
    bitmap->SetBitmap(wxBitmap(img));
    this->Layout();
}

void AppMainWindow::BitmapZoomIn()
{
    bitmap->ZoomInBitmap();
}

void AppMainWindow::BitmapZoomOut()
{
    bitmap->ZoomOutBitmap();
}

void AppMainWindow::BitmapRotate(wxDouble radians)
{
    bitmap->SetAngleRotationRadians(radians);
}

wxDouble AppMainWindow::GetBitmapRotationRadians()
{
    return bitmap->GetAngleRotationRadians();
}
