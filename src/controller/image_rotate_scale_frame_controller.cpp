#include "image_rotate_scale_frame_controller.hpp"

#ifndef IRSFC
#define IRSFC ImageRotateScaleFrameController
#endif

IRSFC::IRSFC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void IRSFC::SetView(wxWindow *view)
{
    this->view = view;
}
