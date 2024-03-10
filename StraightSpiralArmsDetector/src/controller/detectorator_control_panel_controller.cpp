#include "detectorator_control_panel_controller.hpp"

#ifndef DCPC
#define DCPC DetectoratorControlPanelController
#endif
#ifndef CastDCP
#define CastDCP dynamic_cast<DetectoratorControlPanel *>(view)
#endif

DCPC::DCPC(BufferedBitmap *bitmap, ProcessedImage *procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
    azsm = new AdaptiveZhangSuenMethod();
}

void DCPC::SetView(wxWindow *view)
{
    this->view = view;
}

void DCPC::RunDetectorator()
{
    float binaryThresh = (float)CastDCP->GetBinaryThresh();
    float gaussConst = (float)CastDCP->GetGaussConst();
    float compressPercentage = (float)CastDCP->GetCompressPercentage();
    int gaussBlockSize = CastDCP->GetGaussBlockSize();

    AdaptiveZhangSuenParameters azsmParams{
        binaryThresh, gaussConst, compressPercentage, gaussBlockSize
    };

    cv::Mat img = procImage->GetProcessedImage();
    cv::Mat dst = cv::Mat();
    cv::cvtColor(img, dst, cv::COLOR_RGB2GRAY);

    img = azsm->execute(dst, azsmParams);

    procImage->SetProcessedImage(img);
    cv::cvtColor(img, dst, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(dst)));
}
