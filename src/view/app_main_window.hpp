#ifndef APP_MAIN_WINDOW_H
#define APP_MAIN_WINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/numdlg.h>
#include <wx/slider.h>
#include <wx/event.h>
#include "ids_of_controls.hpp"
#include "../model/buffered_bitmap.hpp"
#include "detectorator_control_panel.hpp"
#include "bitmap_control_panel.hpp"

class AppMainWindow : public wxFrame
{
private:
    BufferedBitmap *bitmap;
    wxPanel *mainPanel;
    wxImage loadedImg;
    void UpdateBitmapImage(const wxImage &);
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
public:
    AppMainWindow(const wxString &);
    ~AppMainWindow();
    wxPanel *GetMainPanel();
    BufferedBitmap *GetBitmap();
    wxDouble GetBitmapRotationRadians();
    void BitmapZoomIn();
    void BitmapZoomOut();
    void BitmapRotate(wxDouble);
};

#endif
