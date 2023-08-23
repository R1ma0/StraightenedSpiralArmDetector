#include "AppMainWindow.h"

AppMainWindow::AppMainWindow() : wxFrame(nullptr, wxID_ANY, "Detectorator of strings of galaxies")
{
    wxMenu *menuFile = new wxMenu();
    menuFile->Append(wxID_EXIT);

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "File");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("App loaded");

    Bind(wxEVT_MENU, &AppMainWindow::OnExit, this, wxID_EXIT);
}

void AppMainWindow::OnExit(wxCommandEvent &event)
{
    Close(true);
}