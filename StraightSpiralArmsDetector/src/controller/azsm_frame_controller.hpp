#ifndef AZSM_FRAME_CONTROLLER
#define AZSM_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/activityindicator.h>
#include <opencv2/opencv.hpp>
#include <thread>
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/azsm_control_frame.hpp"
#include "../model/converters.hpp"
#include "../model/processed_image.hpp"
#include "../model/adaptive_zhang_suen_method/adaptive_zhang_suen.hpp"

#ifndef AZSMFC
#define AZSMFC AZSMFrameController
#endif
#ifndef CastAZSMCF
#define CastAZSMCF dynamic_cast<AZSMControlFrame*>(view)
#endif

class AZSMFC : public IController
{
private:
    wxWindow* view;
    ProcessedImage* procImage;
    BufferedBitmap* bitmap;

    wxActivityIndicator* activityIndicator;
    int gbsOldValue;
    void Compute(AdaptiveZhangSuenParameters, wxActivityIndicator*);
    void CreateActivityIndicator();
    void EnableDialogComponents(bool);
public:
    AZSMFC(BufferedBitmap*, ProcessedImage*);
    ~AZSMFC();
    const int GBS_SPIN_DEFAULT_VALUE{ 3 };
    void SetView(wxWindow*) override;
    void RunDetectorator();
    int CheckGBSValue(int);
};

#endif
