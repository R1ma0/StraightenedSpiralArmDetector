#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/log.h>
#include <iostream>
#include "../model/buffered_bitmap.hpp"

enum IDs
{
    ID_LOAD_IMG = 2,
};

class AppMainWindow : public wxFrame
{
private:
    BufferedBitmap *bitmap;
    wxMenu *menuFile;
    wxMenuItem *loadImg;
    wxMenuBar *menuBar;
    wxStatusBar *statusBar;
    wxBoxSizer *sizer;
    wxImage loadedImg;
    void UpdateBitmapImage(const wxImage &);
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
public:
    AppMainWindow(const wxString &);
    ~AppMainWindow();
};

#endif
