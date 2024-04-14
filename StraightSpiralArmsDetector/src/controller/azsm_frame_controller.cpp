#include "azsm_frame_controller.hpp"

AZSMFC::AZSMFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

AZSMFC::~AZSMFC()
{
    wxDELETE(procImage);
    wxDELETE(computeThread);
}

void AZSMFC::SetView(wxWindow* view)
{
    this->view = view;
}

void AZSMFC::RunDetectorator()
{
    AdaptiveZhangSuenParameters azsmParams{
        (float)CastAZSMCF->GetBinaryThresh(),
        (float)CastAZSMCF->GetGaussConst(),
        (float)CastAZSMCF->GetCompressPercentage(),
        CastAZSMCF->GetGaussBlockSize()
    };

    activityIndicator = CreateActivityIndicator(view, wxSize(100, 100));
    activityIndicator->Start();
    activityIndicator->Show();

    EnableDialogComponents(false);

    computeThread = new std::thread{ &AZSMFC::Compute, this, azsmParams, activityIndicator };
    computeThread->detach();
}

void AZSMFC::Compute(AdaptiveZhangSuenParameters azsmParams, wxActivityIndicator* actInd)
{   
    AdaptiveZhangSuenMethod* azsm = new AdaptiveZhangSuenMethod();
    cv::Mat img = procImage->GetProcessedImage();
    cv::Mat dst;
    cv::cvtColor(img, dst, cv::COLOR_RGB2GRAY);

    img = azsm->execute(dst, azsmParams);

    // If the dialog has been closed up to this point, the program will close
    // TO DO: fix that!

    procImage->SetProcessedImage(img);
    cv::cvtColor(img, dst, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(&dst)));

    actInd->Stop();
    actInd->Hide();
    EnableDialogComponents(true);

    delete azsm;
}

void AZSMFC::EnableDialogComponents(bool state)
{
    CastAZSMCF->SetEnableComponents(state);
}