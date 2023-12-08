#ifndef BITMAP_CONTROL_PANEL_CONTROLLER_H
#define BITMAP_CONTROL_PANEL_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include "i_controller.hpp"
#include "../view/app_main_window.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../view/bitmap_control_panel.hpp"
#include "../view/image_rotate_scale_frame.hpp"
#include "../model/processed_image.hpp"
#include "../controller/image_rotate_scale_frame_controller.hpp"

class BitmapControlPanelController : public IController
{
private:
    wxWindow *view;
    ProcessedImage *procImage;
    BufferedBitmap *bitmap;
public:
    BitmapControlPanelController(BufferedBitmap *, ProcessedImage *);
    wxDouble GetCurrRotation();
    void SetView(wxWindow *) override;
    void OnZoomInBitmap();
    void OnZoomOutBitmap();
    void OpenRotateScaleFrame();
};

#endif
