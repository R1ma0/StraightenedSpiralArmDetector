#ifndef IMAGE_ROTATE_SCALE_FRAME_CONTROLLER_H
#define IMAGE_ROTATE_SCALE_FRAME_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include "i_controller.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../model/processed_image.hpp"

class ImageRotateScaleFrameController : public IController
{
private:
    wxWindow *view;
    ProcessedImage *procImage;
    BufferedBitmap *bitmap;
public:
    ImageRotateScaleFrameController(BufferedBitmap *, ProcessedImage *);
    void SetView(wxWindow *) override;
};

#endif
