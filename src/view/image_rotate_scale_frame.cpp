#include "image_rotate_scale_frame.hpp"

#ifndef IRSF
#define IRSF ImageRotateScaleFrame
#endif

IRSF::IRSF
(
    IController *controller
) : wxFrame
(
    NULL, 
    wxID_ANY, 
    "Rotate & Scale"
)
{
    this->controller = controller;
}
