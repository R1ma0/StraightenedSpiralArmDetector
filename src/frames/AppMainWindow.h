#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/log.h>

enum IDs
{
    ID_LOAD_IMG = 2,
};

class AppMainWindow : public wxFrame
{
private:
    wxMenu *menuFile;
    wxMenuItem *loadImg;
    wxMenuBar *menuBar;
    wxStatusBar *statusBar;
    wxImage loadedImg;
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
    void LoadImage(wxFileInputStream &, wxBitmapType);
    void DisplayImageAsBitmap(wxWindow *, wxImage &);
public:
    AppMainWindow(const wxString &);
};

#endif