#include "azsm_frame_controller.hpp"

AZSMFC::AZSMFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
    azsm = new AdaptiveZhangSuenMethod();
}

void AZSMFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMFC::RunDetectorator()
{
    float binaryThresh = (float)CastAZSMCF->GetBinaryThresh();
    float gaussConst = (float)CastAZSMCF->GetGaussConst();
    float compressPercentage = (float)CastAZSMCF->GetCompressPercentage();
    int gaussBlockSize = CastAZSMCF->GetGaussBlockSize();

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
