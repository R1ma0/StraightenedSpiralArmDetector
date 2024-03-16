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
#include "../controller/i_controller.hpp"
#include "../controller/app_main_window_controller.hpp"

#ifndef AMW
#define AWM AppMainWindow
#endif
#ifndef CastAMWC
#define CastAMWC dynamic_cast<AppMainWindowController *>(mainController)
#endif

class AWM : public wxFrame
{
private:
    IController* mainController;
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
    AWM(const wxString&, IController*);
    ~AWM();
    BufferedBitmap* GetBufferedBitmap() { return bitmap; }
    void UpdateBitmap(wxBitmap);
};

#endif
