#include "detectorator_control_panel_controller.hpp"

DCPC::DCPC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void DCPC::SetView(wxWindow *view)
{
    selfView = view;
}
