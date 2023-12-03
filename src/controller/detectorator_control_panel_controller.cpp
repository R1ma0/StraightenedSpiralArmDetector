#include "detectorator_control_panel_controller.hpp"
#include <iostream>

DCPC::DCPC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

void DCPC::SetView(wxWindow *view)
{
    selfView = view;
}

void DCPC::RunDetectorator()
{
    auto azsm = new AdaptiveZhangSuenMethod();
    AdaptiveZhangSuenParameters azsmParams{
        190.f, -5.f, 20.f, 201
    };

    cv::Mat img = procImage->GetProcessedImage();
    cv::Mat dst = cv::Mat();
    cv::cvtColor(img, dst, cv::COLOR_RGB2GRAY);

    img = azsm->execute(dst, azsmParams);

    procImage->SetProcessedImage(img);
    cv::cvtColor(img, dst, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(dst)));
}
