#ifndef BITMAP_CONTROL_PANEL_H
#define BITMAP_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/numdlg.h>
#include "ids_of_controls.hpp"
#include "buffered_bitmap.hpp"
#include "app_main_window.hpp"
#include "../model/processed_image.hpp"
#include "../model/converters.hpp"

class BitmapControlPanel : public wxPanel
{
private:
    BufferedBitmap *bitmap;
    ProcessedImage *procImage;
    void CreateControls();
    void BindEventHandlers();
    void OnZoomIn(wxCommandEvent &);
    void OnZoomOut(wxCommandEvent &);
    void OnAngleChangeBtn(wxCommandEvent &);
    void OnAngleChangeSlider(wxCommandEvent &);
public:
    BitmapControlPanel(wxFrame *, BufferedBitmap *, ProcessedImage *);
};

#endif
