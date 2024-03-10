#ifndef APP_MAIN_WINDOW_CONTROLLER_H
#define APP_MAIN_WINDOW_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../view/image_rotate_scale_frame.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../model/processed_image.hpp"
#include "../model/converters.hpp"
#include "../controller/image_rotate_scale_frame_controller.hpp"

class AppMainWindowController : public IController
{
private:
    wxWindow *view;
    ProcessedImage* procImage;
public:
    AppMainWindowController();
    ~AppMainWindowController();
    wxBitmap GetBitmapImage();
    ProcessedImage *GetProcessedImage();
    bool LoadImage(const std::string path);
    bool SaveImage(const std::string path);
    void SetView(wxWindow *) override;
    void OpenRotateScaleFrame(BufferedBitmap *);
    void ZoomInBitmap(BufferedBitmap *);
    void ZoomOutBitmap(BufferedBitmap *);
};

#endif
