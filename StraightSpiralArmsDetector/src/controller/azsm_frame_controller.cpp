#include "azsm_frame_controller.hpp"

AZSMFC::AZSMFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
    azsm = new AdaptiveZhangSuenMethod();
    gbsOldValue = GBS_SPIN_DEFAULT_VALUE;
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
    cv::Mat* dst = new cv::Mat();
    cv::cvtColor(img, *dst, cv::COLOR_RGB2GRAY);

    img = azsm->execute(*dst, azsmParams);

    procImage->SetProcessedImage(img);
    cv::cvtColor(img, *dst, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(dst)));

    delete dst;
}

int AZSMFC::CheckGBSValue(int value)
{
    int newValue = value;

    if (value % 2 == 0)
    {
        if (value - gbsOldValue > 0) { newValue = value + 1; }
        if (value - gbsOldValue < 0) { newValue = value - 1; }
    }

    gbsOldValue = newValue;

    return newValue;
}
