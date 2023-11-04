#ifndef DETECTORATOR_CONTROL_PANEL_H
#define DETECTORATOR_CONTROL_PANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "buffered_bitmap.hpp"
#include "../model/processed_image.hpp"

class DetectoratorControlPanel : public wxPanel
{
private:
    BufferedBitmap *bitmap;
    ProcessedImage *procImage;
public:
    DetectoratorControlPanel(wxFrame *, BufferedBitmap *, ProcessedImage *);
};

#endif
