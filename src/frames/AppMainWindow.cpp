#include "AppMainWindow.h"

AppMainWindow::AppMainWindow(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);

    CreateControls();
    BindEventHandlers();
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
    menuBar->Append(menuFile, "File");
    SetMenuBar(menuBar);
    
    CreateStatusBar();
}

void AppMainWindow::BindEventHandlers()
{
    Bind(wxEVT_MENU, &AppMainWindow::OnLoadImg, this, ID_LOAD_IMG);
    Bind(wxEVT_MENU, &AppMainWindow::OnExit, this, wxID_EXIT);
}

void AppMainWindow::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void AppMainWindow::LoadImage(wxFileInputStream &stream, wxBitmapType type)
{
    loadedImg = wxImage(stream, type);
}

void AppMainWindow::DisplayImageAsBitmap(wxWindow *parent, wxImage &img)
{
    wxStaticBitmap *bitmap = new wxStaticBitmap(parent, wxID_ANY, wxBitmap(img));
}

void AppMainWindow::OnLoadImg(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(
        this, 
        "Select image", "", "", 
        ("PNG & JPG files (*.png;*.jpg)|*.png;*.jpg"), 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) { return; }

    wxFileInputStream inputStream(openFileDialog.GetPath());

    if (!inputStream.IsOk())
    {
        wxLogStatus(wxT("Could not open the file '" + openFileDialog.GetFilename() + "'"));

        return;
    }
    else
    {
        LoadImage(inputStream, wxBITMAP_TYPE_ANY);
        DisplayImageAsBitmap(this, loadedImg);

        wxLogStatus(wxT("File '" + openFileDialog.GetFilename() + "' open"));

        return;
    }
}