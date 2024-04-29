#include "azsm_frame_controller.hpp"

AZSMFC::AZSMFC(BufferedBitmap* bitmap, ProcessedImage* procImage)
{
    this->bitmap = bitmap;
    this->procImage = procImage;
}

AZSMFC::~AZSMFC()
{
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
    cv::Mat* img = new cv::Mat(procImage->GetProcessedImage());
    cv::cvtColor(*img, *img, cv::COLOR_RGB2GRAY);

    *img = azsm->execute(*img, azsmParams);

    // If the dialog has been closed up to this point, the program will close
    // TO DO: fix that!

    cv::cvtColor(*img, *img, cv::COLOR_GRAY2RGB);
    bitmap->SetBitmap(wxBitmap(MatToWxImage(img)));

    actInd->Stop();
    actInd->Hide();
    EnableDialogComponents(true);

    wxDELETE(azsm);
    wxDELETE(img);
}

void AZSMFC::EnableDialogComponents(bool state)
{
    CastAZSMCF->SetEnableComponents(state);
}