#ifndef IMAGE_ROTATE_SCALE_FRAME_CONTROLLER_H
#define IMAGE_ROTATE_SCALE_FRAME_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <opencv2/opencv.hpp>
#include "i_controller.hpp"
#include "../model/converters.hpp"
#include "../view/buffered_bitmap.hpp"
#include "../model/processed_image.hpp"

struct RotateScaleValues
{
    int angle;
    int x;
    int y;
};

class ImageRotateScaleFrameController : public IController
{
private:
    wxWindow *view;
    ProcessedImage *procImage;
    BufferedBitmap *bitmap;
public:
    ImageRotateScaleFrameController(BufferedBitmap *, ProcessedImage *);
    void SetView(wxWindow *) override;
    void SetRotateScaleValues(RotateScaleValues);
    RotateScaleValues GetRotateScaleValues();
};

#endif
