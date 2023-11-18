#ifndef DETECTORATOR_CONTROL_PANEL_H
#define DETECTORATOR_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include "ids_of_controls.hpp"
#include "buffered_bitmap.hpp"
#include "../model/processed_image.hpp"

class DetectoratorControlPanel : public wxPanel
{
private:
    BufferedBitmap *bitmap;
    ProcessedImage *procImage;
    void CreateControls();
    void BindEventHandlers();
    void OnResizeImg(wxCommandEvent &);
    void OnUseThreshBin(wxCommandEvent &);
public:
    DetectoratorControlPanel(wxFrame *, BufferedBitmap *, ProcessedImage *);
};

#endif
