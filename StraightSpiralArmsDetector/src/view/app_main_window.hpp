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
#include "buffered_bitmap.hpp"
#include "detectorator_control_panel.hpp"
#include "bitmap_control_panel.hpp"
#include "../controller/i_controller.hpp"
#include "../controller/app_main_window_controller.hpp"

class AppMainWindow : public wxFrame
{
private:
    IController *mainController;
    BufferedBitmap *bitmap;
    wxMenuItem *saveImg;
    wxString *fileFilters;
    wxBoxSizer *sizerMain;
    wxBoxSizer *bitmapControlSizer;
    wxBoxSizer *detectoratorControlSizer;
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void OnSaveImg(wxCommandEvent &);
    void OnRotateScale(wxCommandEvent &);
    void OnImageZoomIn(wxCommandEvent &);
    void OnImageZoomOut(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
    void AllowSavingImage(bool);
public:
    AppMainWindow(const wxString &, IController *);
    ~AppMainWindow();
    BufferedBitmap *GetBufferedBitmap() { return bitmap; }
    void UpdateBitmap(wxBitmap);
    void SetBitmapControlPanel(wxPanel *);
    void SetDetectoratorControlPanel(wxPanel *);
};

#endif
