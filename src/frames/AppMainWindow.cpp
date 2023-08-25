#include "AppMainWindow.h"

AppMainWindow::AppMainWindow() : wxFrame(nullptr, wxID_ANY, "Detectorator of strings of galaxies")
{
    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_LOAD_IMG, wxT("Load image\tCtrl-O"), "Opening and loading an image for processing");
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "File");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("App loaded");

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
        "Load image file", "", "", ("PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg"), 
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    wxFileInputStream inputStream(openFileDialog.GetPath());

    if (!inputStream.IsOk())
    {
        SetStatusText(wxT("Could not open the file " + openFileDialog.GetPath()));
        return;
    }
    else
    {
        SetStatusText(wxT("The " + openFileDialog.GetPath() + " is open"));
        return;
    }
}