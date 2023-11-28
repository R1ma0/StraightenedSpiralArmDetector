#ifndef DETECTORATOR_CONTROL_PANEL_CONTROLLER
#define DETECTORATOR_CONTROL_PANEL_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/detectorator_control_panel.hpp"
#include "../model/processed_image.hpp"

#define DCPC DetectoratorControlPanelController

class DetectoratorControlPanelController : public IController
{
private:
    wxWindow *selfView;
    ProcessedImage *procImage;
    BufferedBitmap *bitmap;
public:
    DetectoratorControlPanelController(BufferedBitmap *, ProcessedImage *);
    void SetView(wxWindow *) override;
};

#endif
