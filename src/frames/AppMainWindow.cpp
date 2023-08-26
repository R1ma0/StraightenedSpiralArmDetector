#include "AppMainWindow.h"

AppMainWindow::AppMainWindow(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    CreateControls();
    BindEventHandlers();
}

void AppMainWindow::CreateControls()
{
    menuFile = new wxMenu();
    loadImg = new wxMenuItem(
        menuFile, ID_LOAD_IMG, wxT("Load image\tCtrl-O"), 
        "Opening and loading an image for processing"
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

void AppMainWindow::OnLoadImg(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(
        this, 
        "Load image file", "", "", 
        ("PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg"), 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxFileInputStream inputStream(openFileDialog.GetPath());

    if (!inputStream.IsOk())
    {
        wxLogStatus(wxT("Could not open the file " + openFileDialog.GetPath()));
        return;
    }
    else
    {
        wxLogStatus(wxT("The " + openFileDialog.GetPath() + " is open"));
        return;
    }
}