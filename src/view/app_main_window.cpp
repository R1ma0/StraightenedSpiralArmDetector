#include "app_main_window.hpp"

AppMainWindow::AppMainWindow(const wxString &title) : wxFrame(
    nullptr, wxID_ANY, title
)
{
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    CreateControls();
    BindEventHandlers();
}

AppMainWindow::~AppMainWindow() 
{
    free(bitmap);
}

void AppMainWindow::CreateControls()
{
    menuFile = new wxMenu();
    loadImg = new wxMenuItem(
        menuFile, ID_LOAD_IMG, wxT("Load image\tCtrl-O"), 
        wxT("Opening and loading an image for processing")
    );
    menuFile->Append(loadImg);
    menuFile->Append(wxID_EXIT);

    menuBar = new wxMenuBar();
    menuBar->Append(menuFile, wxT("File"));
    SetMenuBar(menuBar);
    
    CreateStatusBar();

    bitmap = new BufferedBitmap(
        this, wxID_ANY, wxBitmap(wxSize(1, 1)), wxDefaultPosition, 
        FromDIP(wxSize(500, 200)), 0
    );

    zoomControls = new wxBoxSizer(wxHORIZONTAL);
    zoomInBtn = new wxButton(this, ID_ZOOM_IN, wxT("+"));
    zoomOutBtn = new wxButton(this, ID_ZOOM_OUT, wxT("-"));
    zoomValue = new wxStaticText(this, wxID_ANY, "");


    zoomControls->Add(zoomInBtn, 0, wxALIGN_CENTER_VERTICAL, FromDIP(5));
    zoomControls->Add(zoomValue, 0, wxALIGN_CENTER_VERTICAL, FromDIP(5));
    zoomControls->Add(zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL, FromDIP(5));

    EnableZoomControls(false);
    UpdateZoomValue();

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(bitmap, 1, wxEXPAND | wxALL, FromDIP(10));
    sizer->Add(zoomControls, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, FromDIP(10));

    this->SetSizerAndFit(sizer);
}

void AppMainWindow::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AppMainWindow::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &AppMainWindow::OnZoomIn, this, ID_ZOOM_IN);
    Bind(wxEVT_BUTTON, &AppMainWindow::OnZoomOut, this, ID_ZOOM_OUT);
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
    EnableZoomControls(true);
}
void AppMainWindow::UpdateBitmapImage(const wxImage &img)
{
    bitmap->SetBitmap(wxBitmap(img));
    this->Layout();
}

void AppMainWindow::OnZoomIn([[maybe_unused]] wxCommandEvent &event)
{
    bitmap->ZoomInBitmap();
    UpdateZoomValue();
}

void AppMainWindow::OnZoomOut([[maybe_unused]] wxCommandEvent &event)
{
    bitmap->ZoomOutBitmap();
    UpdateZoomValue();
}

void AppMainWindow::UpdateZoomValue()
{
    zoomValue->SetLabel(std::to_string(bitmap->GetZoomMultiplier()));
}

void AppMainWindow::EnableZoomControls(bool condition)
{
    zoomInBtn->Enable(condition);
    zoomOutBtn->Enable(condition);
    zoomValue->Enable(condition);
}
