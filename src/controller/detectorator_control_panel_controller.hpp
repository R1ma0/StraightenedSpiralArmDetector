#ifndef DETECTORATOR_CONTROL_PANEL_CONTROLLER
#define DETECTORATOR_CONTROL_PANEL_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/detectorator_control_panel.hpp"
#include "../model/converters.hpp"
#include "../model/processed_image.hpp"
#include "../model/detectorator/adaptive_zhang_suen.hpp"

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
    void  RunDetectorator();
};

#endif
