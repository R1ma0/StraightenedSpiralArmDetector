#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/numdlg.h>
#include <wx/slider.h>
#include <wx/event.h>
#include "../model/buffered_bitmap.hpp"

enum IDs
{
    ID_LOAD_IMG = 2,
    ID_ZOOM_IN,
    ID_ZOOM_OUT,
    ID_ANGLE_CHANGE,
    ID_ANGLE_CHANGE_SLIDER,
};

class AppMainWindow : public wxFrame
{
private:
    BufferedBitmap *bitmap;
    wxMenu *menuFile;
    wxMenu *menuImage;
    wxMenuItem *loadImg;
    wxMenuItem *zoomIn;
    wxMenuItem *zoomOut;
    wxMenuBar *menuBar;
    wxStatusBar *statusBar;
    wxBoxSizer *sizerMain;
    wxBoxSizer *sizerLeft;
    wxBoxSizer *sizerRight;
    wxBoxSizer *imgControlPanel;
    wxButton *zoomInBtn;
    wxButton *zoomOutBtn;
    wxButton *askAngleBtn;
    wxSlider *imgRotationSlider;
    wxImage loadedImg;
    void UpdateBitmapImage(const wxImage &);
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void OnZoomIn(wxCommandEvent &);
    void OnZoomOut(wxCommandEvent &);
    void OnAngleChangeBtn(wxCommandEvent &);
    void OnAngleChangeSlider(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
    void EnableControls(bool);
public:
    AppMainWindow(const wxString &);
    ~AppMainWindow();
};

#endif
