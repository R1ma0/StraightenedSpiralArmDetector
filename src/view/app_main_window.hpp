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
#include "../model/processed_image.hpp"
#include "../model/converters.hpp"

class AppMainWindow : public wxFrame
{
private:
    IController *mainController;
    BufferedBitmap *bitmap;
    ProcessedImage *procImage;
    wxMenuItem *saveImg;
    wxString *fileFilters;
    void OnExit(wxCommandEvent &);
    void OnLoadImg(wxCommandEvent &);
    void OnSaveImg(wxCommandEvent &);
    void CreateControls();
    void BindEventHandlers();
    void UpdateBitmapImage();
public:
    AppMainWindow(const wxString &, IController *);
    ~AppMainWindow();
    void AllowSavingImage(bool);
};

#endif
