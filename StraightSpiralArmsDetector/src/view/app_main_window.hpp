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
#include "../controller/app_main_window_controller.hpp"
#include "../controller/i_controller.hpp"

#ifndef AMW
#define AMW AppMainWindow
#endif
#ifndef CastAMWC
#define CastAMWC dynamic_cast<AppMainWindowController *>(controller)
#endif

class AMW : public wxFrame
{
private:
    IController* controller;
    BufferedBitmap* bitmap;
    wxMenuItem* saveImg;
    wxBoxSizer* sizerMain;
    void OnExit(wxCommandEvent&);
    void OnLoadImg(wxCommandEvent&);
    void OnSaveImg(wxCommandEvent&);
    void OnRotateScale(wxCommandEvent&);
    void OnImageZoomIn(wxCommandEvent&);
    void OnImageZoomOut(wxCommandEvent&);
    void OnUseAZSMethod(wxCommandEvent&);
    void OnUseMultipleProcessing(wxCommandEvent&);
    void CreateControls();
    void BindEventHandlers();
    void AllowSavingImage(bool);
public:
    AMW(const wxString&, IController*);
    ~AMW();
    BufferedBitmap* GetBufferedBitmap() { return bitmap; }
    void UpdateBitmap(wxBitmap);
};

#endif
