#ifndef AZSM_FRAME_CONTROLLER
#define AZSM_FRAME_CONTROLLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include <thread>
#include "i_controller.hpp"
#include "converters.hpp"
#include "processed_image.hpp"
#include "../view/proc_activity_indicator.hpp"
#include "../view/app_main_window.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/azsm_control_frame.hpp"
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
    std::thread* computeThread;
    wxActivityIndicator* activityIndicator;
    void Compute(AdaptiveZhangSuenParameters, wxActivityIndicator*);
    void EnableDialogComponents(bool);
public:
    AZSMFC(BufferedBitmap*, ProcessedImage*);
    ~AZSMFC();
    void SetView(wxWindow*) override;
    void RunDetectorator();
};

#endif
