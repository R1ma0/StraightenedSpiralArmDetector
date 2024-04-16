#ifndef APP_MAIN_WINDOW_CONTROLLER_H
#define APP_MAIN_WINDOW_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "configurator.hpp"
#include "../view/app_main_window.hpp"
#include "../view/image_rotate_scale_frame.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/azsm_control_frame.hpp"
#include "../view/azsm_multiple_processing_frame.hpp"
#include "../model/processed_image.hpp"
#include "../model/converters.hpp"
#include "../model/constants.hpp"
#include "../controller/image_rotate_scale_frame_controller.hpp"
#include "../controller/azsm_frame_controller.hpp"
#include "../controller/azsm_multiple_processing_frame_controller.hpp"

#ifndef AMWC
#define AMWC AppMainWindowController
#endif
#ifndef CastAMW
#define CastAMW dynamic_cast<AppMainWindow*>(view)
#endif

class AMWC : public IController
{
private:
    wxWindow* view;
    ProcessedImage* procImage;
    Configurator* configurator;
    void InitModalDialog(wxDialog*, wxSize = wxDefaultSize);
public:
    AMWC(Configurator*);
    ~AMWC();
    wxBitmap GetBitmapImage();
    ProcessedImage* GetProcessedImage();
    bool LoadImage();
    bool SaveImage();
    void SetView(wxWindow*) override;
    void OpenRotateScaleFrame(BufferedBitmap*);
    void OpenAZSMethodFrame(BufferedBitmap*);
    void OpenAZSMMultipleProcessingFrame();
    void ZoomInBitmap(BufferedBitmap*);
    void ZoomOutBitmap(BufferedBitmap*);
};

#endif
